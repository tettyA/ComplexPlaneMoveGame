#include "stdafx.h"
#include "sEdit.h"

#include "FileReadWriter.h"


#ifdef VERSION_BETA

void sEdit::draw()const {
	if (isVisibleKakesen) {
		for (int i = -100; i < 100; i++) {
			//横
			Line(origin.movedBy(-500, i * pmul), origin.movedBy(500, i * pmul)).draw(1, Palette::Gray);
			//縦
			Line(origin.movedBy(i * pmul, -500), origin.movedBy(i * pmul, 500)).draw(1, Palette::Gray);
		}
	}

	// X軸（横線）
	Line(origin.movedBy(-400, 0), origin.movedBy(400, 0)).draw(2, Palette::Red);
	font(U"Im").draw(20, Point{ origin.x + 2,2 }, Palette::Blue);

	// Y軸（縦線）
	Line(origin.movedBy(0, -300), origin.movedBy(0, 300)).draw(2, Palette::Blue);
	font(U"Re").draw(20, Point{ Scene::Width() - 28, origin.y - 23 }, Palette::Red);

	// 原点を強調
	Circle(origin, cr).draw(Palette::Purple);
	Point cursorpos = Cursor::Pos();
	int ix = (int)((double)(cursorpos.x - origin.x) / (double)(pmul));
	int iy = (int)((double)-(cursorpos.y - origin.y) / (double)(pmul));
	Circle({ ix * pmul + origin.x,-iy * pmul + origin.y }, cr).draw(Palette::Red.withAlpha(128));
	 
	Circle({ cursorpos.x,cursorpos.y }, cr).draw(Palette::Grey.withAlpha(128));
	c.startpoint.Draw(Palette::Aqua);
	c.goalpoint.Draw(Palette::Green);

	font(U"{}"_fmt(Cursor::Pos())).draw(18, Vec2{ 0,0 }, Palette::Brown);
	font(U"({},{},{})"_fmt(ix, iy,addobjectediting)).draw(18, Vec2{ 130,0 }, Palette::Brown);
	font(U"obj:{},cmd:{}"_fmt(c.pobjs.size(), c.cmds.size())).draw(17, Vec2{ 260,0 }, Palette::Brown);
	font(U"{}"_fmt(filepath)).draw(17, Vec2{ 0,20 }, Palette::Brown);

	for (int i = 0; i < c.pobjs.size(); i++) {
		c.pobjs[i].draw();
	}

	for (int i = 0; i < c.cmds.size(); i++) {
		c.cmds[i].draw(i);
	}
}



void sEdit::update() {

	Point cursorpos = Cursor::Pos();
	int ix = (int)((double)(cursorpos.x - origin.x) / (double)(pmul));
	int iy = (int)((double)-(cursorpos.y - origin.y) / (double)(pmul));

	//メニューバー処理
	if (const auto item = menuBar.update()) {
		if (item == MenuBarItemIndex{ 0,3 }) {//タイトルに戻る
			changeScene(sstate::title);
		}
		if (item == MenuBarItemIndex{ 0,0 }) {//新規作成
			c.cmds = std::vector<cmd>();
			c.pobjs = std::vector<pointobject>();
			c.startpoint.Setfont(font);
			c.goalpoint.Setfont(font);

			c.startpoint.at = { 5,5 };
			c.goalpoint.at = { 10,10 };
			c.startpoint.text = U"開始地点";
			c.goalpoint.text = U"目標地点";
			c.startpoint.textoffset = { 10,10 };
			c.goalpoint.textoffset = { 10,-30 };

			filepath = invalidfilepath;
		}
		if (item == MenuBarItemIndex{ 0,1 }) {//開く

			Optional<String> tfp =
				Dialog::OpenFile({ FileFilter{ U"複素数平面ゲームマップ", { U"fgp" } } }).value();

			if (tfp == none)return;
			FilePath fp = tfp.value();

			filepath = fp.toUTF32();

			CourseLoader(c, fp);
		}
		if (item == MenuBarItemIndex{ 0,2 }) {//保存
			if (filepath == invalidfilepath) {
				Optional<String> tfp =
					Dialog::SaveFile({ FileFilter{ U"複素数平面ゲームマップ", { U"fgp" } } }).value();
				if (tfp == none)return;
				FilePath fp = tfp.value();
				TextWriter tw{ fp };
				if (not tw)return;
				filepath = fp.toUTF32();
			}
			CourseWriter(c, filepath);
		}
		if (item == MenuBarItemIndex{ 1,0 }) {//掛線表示切替
			menuBar.setItemChecked(*item, !isVisibleKakesen);
			isVisibleKakesen = !isVisibleKakesen;
		}
	}

#pragma region 物体追加時の挙動
	if (addobjectediting && MouseL.down()) {
		if (
			handlingobj.type == pointobject::objtype::checkpoint ||
			handlingobj.type == pointobject::objtype::pstop ||
			handlingobj.type == pointobject::objtype::preset
			) {
			c.pobjs.emplace_back(handlingobj);
			addobjectediting = false;
		}
		else if (handlingobj.p2 == pvalidp2) {
			handlingobj.p2 = complex(ix, iy);
		}
		else
		{
			c.pobjs.emplace_back(handlingobj);
			addobjectediting = false;
		}
	}
	//右クリックをすると連続で押せるようにする．
	if (addobjectediting && MouseR.down()) {

		if (handlingobj.p2 == pvalidp2) {
			handlingobj.p2 = complex(ix, iy);
		}
		else {
			c.pobjs.emplace_back(handlingobj);
			handlingobj.p1 = handlingobj.p2;
			handlingobj.p2 = complex(ix, iy);
		}
	}
	SimpleGUI::ListBox(lbs, { 0, 30 }, 230);
	if (SimpleGUI::Button(U"\U000F0415　物体を追加", { 0,190 })) {
		addobjectediting = true;
		handlingobj.p2 = pvalidp2;
		handlingobj.p1 = complex(ix, iy);
		if (lbs.selectedItemIndex == 0) {
			handlingobj.type = pointobject::objtype::checkpoint;
		}
		else if (lbs.selectedItemIndex == 1) {
			handlingobj.type = pointobject::objtype::pstop;
		}
		else if (lbs.selectedItemIndex == 2) {
			handlingobj.p2 = pvalidp2;
			handlingobj.type = pointobject::objtype::wstop;
		}
		else if (lbs.selectedItemIndex == 3) {
			handlingobj.type = pointobject::objtype::preset;
		}
		else if (lbs.selectedItemIndex == 4) {

			handlingobj.p2 = pvalidp2;
			handlingobj.type = pointobject::objtype::wreset;
		}
		lbs.selectedItemIndex;
	}
	if (addobjectediting) {
		if (handlingobj.p2 == pvalidp2)
			handlingobj.p1 = complex(ix, iy);
		else handlingobj.p2 = complex(ix, iy);
		handlingobj.draw();
	}


#pragma endregion
#pragma region 物体移動，削除関連
	for (int i = 0; i < c.pobjs.size(); i++) {
		if (int tmp = c.pobjs[i].mouseOver()) {
			Print << c.pobjs.size();
			Cursor::RequestStyle(CursorStyle::Hand);
			if (MouseL.pressed()) {
				Point cursorpos = Cursor::Pos();
				if (tmp == 1)
					c.pobjs[i].p1 = complex(ix, iy);
				else if (tmp == 2)
					c.pobjs[i].p2 = complex(ix, iy);
			}
			else if (MouseR.pressed() && (!addobjectediting)) {
				c.pobjs.erase(c.pobjs.begin() + i);
			}
		}
	}
#pragma endregion

#pragma region コマンド追加
	SimpleGUI::ListBox(lbscmd, { 0,220 });
	SimpleGUI::TextBox(tescmd, { 0,390 });
	if (SimpleGUI::Button(U"演算を追加", { 0,430 })) {
		cmd tmpcmd;
		
		tmpcmd.value1 = std::stoi(tescmd.text.toWstr());
		if (lbscmd.selectedItemIndex == 0) {
			tmpcmd.cmdtype = cmd::type::addre;
		}
		else if (lbscmd.selectedItemIndex == 1) {
			tmpcmd.cmdtype = cmd::type::addim;
		}
		else if (lbscmd.selectedItemIndex == 2) {
			tmpcmd.cmdtype = cmd::type::adddeg;
		}
		else if (lbscmd.selectedItemIndex == 3) {
			tmpcmd.cmdtype = cmd::type::addr;
		}

		c.cmds.emplace_back(tmpcmd);
	}
#pragma endregion
#pragma region コマンド編集
	for (int i = 0; i < c.cmds.size(); i++) {
		if (c.cmds[i].MouseOver(i)) {
			if (MouseR.down()) {
				c.cmds.erase(c.cmds.begin() + i);
			}
			else if (MouseL.down() && KeyLControl.pressed() && KeyLShift.pressed()) {
				if( c.cmds[i].nokori!=cardinf)
				c.cmds[i].nokori--;


				if (c.cmds[i].nokori <= 0)c.cmds[i].nokori = cardinf;
			}
			else if (MouseL.down() && KeyLControl.pressed()) {
				if (c.cmds[i].nokori == cardinf) {
					c.cmds[i].nokori = -1;
				}
				c.cmds[i].nokori++;
			}
		}
	}
#pragma endregion


#pragma region 開始地点と目標地点の移動
	Circle sp = Circle(Vec2{ c.startpoint.at.real() * pmul + origin.x,-c.startpoint.at.imag() * pmul + origin.y }, cr + 10);
	Circle gp = Circle(Vec2{ c.goalpoint.at.real() * pmul + origin.x,-c.goalpoint.at.imag() * pmul + origin.y }, cr + 10);
	if (sp.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
		if (MouseL.pressed()) {
			Point cursorpos = Cursor::Pos();
			c.startpoint.at = complex((int)((double)(cursorpos.x - origin.x) / (double)(pmul)), (int)((double)-(cursorpos.y - origin.y) / (double)(pmul)));
		}
	}
	if (gp.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
		if (MouseL.pressed()) {
			Point cursorpos = Cursor::Pos();
			c.goalpoint.at = complex((int)((double)(cursorpos.x - origin.x) / (double)(pmul)), (int)((double)-(cursorpos.y - origin.y) / (double)(pmul)));
		}
	}
#pragma endregion

	if (SimpleGUI::Button(U"\U000F1936 テストプレイ", { 0,500 })) {
		getData().coursenum = COURSENUM_TESTPLAY;
		Window::SetTitle(filepath);
		CourseWriter(c, _path_course UR"(999999.fgp)");
		changeScene(sstate::testgame,1.0s);
	}

	menuBar.draw();
}

#endif