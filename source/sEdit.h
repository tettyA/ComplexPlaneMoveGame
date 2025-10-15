#pragma once

#include "stdafx.h"

#include <vector>

#include "header.h"


#include "cmd.h"

#include "point.h"
#include "textedpoint.h"
#include "playerpoint.h"
#include "pointobject.h"

#include "course.h"

#include "FileReadWriter.h"

#ifdef VERSION_BETA

#define pvalidp2 ( point{ 10000,10000 })
#define pnorelationship (point{10001,10000})

#define invalidfilepath (U"VOIDVOIDVOIDV")
class sEdit:public App::Scene
{
public:
	sEdit(const InitData& init) :IScene{ init } {
		font = getData().font;
		c.startpoint.Setfont(font);
		c.goalpoint.Setfont(font);

		c.startpoint.at = { 5,5 };
		c.goalpoint.at = { 10,10 };
		c.startpoint.text = U"開始地点";
		c.goalpoint.text = U"目標地点";
		c.startpoint.textoffset = { 10,10 };
		c.goalpoint.textoffset = { 10,-30 };

		filepath = invalidfilepath;

		if (Window::GetTitle()[0] == U'T') {
			filepath = Window::GetTitle().substr(12).toUTF32();
			CourseLoader(c,_path_course UR"(999999.fgp)");
		}

		Window::SetTitle(U"EDIT");
	}

	void draw() const override;
	void update() override;

	course c;
	//textedpoint startpoint;
	//textedpoint goalpoint;
private:
	const Point origin = Scene::Center();
	Font font;

	bool isVisibleKakesen = false;
	bool isVisibleMb = false;
	const Array<std::pair<String, Array<String>>> items
	{
		{ U"ファイル(&F)", { U"\U000F039D　新規作成", U"開く",U"\U000F0193　保存", U"\U000F0731　タイトルに戻る"}},
		{ U"編集", {  U"\U000F02C1　掛線を表示"} },
	};
	ListBoxState lbs{ {
		U"チェックポイント",U"通行止点",U"通行止壁",U"リセット点",U"リセット壁"
	} };
	ListBoxState lbscmd{ {
			U"実数演算",U"虚数演算",U"回転",U"半径"
} };
	TextEditState tescmd;
	//std::vector<cmd>cmds;
	SimpleMenuBar menuBar{ items };

	std::u32string filepath;
	
	pointobject handlingobj;
	bool addobjectediting = false;
//	std::vector<pointobject>pobjs;
};


#endif