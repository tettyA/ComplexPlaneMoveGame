#include "stdafx.h"
#include "gamemgr.h"

#include <filesystem>

void cmdexecute(int &i, course& c,playerpoint &p,Moveanimation&mav) {
	if (c.cmds[i].nokori != cardinf) {
		if (c.cmds[i].nokori <= 0) {
			i = 999999;
			return;
		}
		c.cmds[i].nokori--;
	}
	if (mav.nowanimationing) {
		mav.from = mav.from + (mav.to - mav.from) * ((Scene::Time() - mav.begintime) / animeduration);
	}
	else {
		mav.from = mav.bfrom = p.at.at;
	}
	mav.begintime = Scene::Time();
	
	mav.nowanimationing = true;
	switch (c.cmds[i].cmdtype)
	{
	case cmd::type::addre:
		p.at.at += c.cmds[i].value1;
		break;
	case cmd::type::addim:
		p.at.at += std::complex<double>(0.0, c.cmds[i].value1);
		break;
	case cmd::type::addr:
		p.at.at = std::polar(abs(p.at.at) + c.cmds[i].value1, arg(p.at.at));
		break;
	case cmd::type::adddeg:
		p.at.at *= std::complex<double>(cos(c.cmds[i].value1 _to_rad), sin(c.cmds[i].value1 _to_rad));
		break;
	}
	mav.to = p.at.at;

}


void gamemgr::update() {

	player.Update();
	if (KeyR.down()) {
		changeScene(sstate::game, 2.5s);
	}
	for (int i = 0; i < c.cmds.size(); i++) {
		if (c.cmds[i].MouseOver(i)) {
			if (MouseL.down()) {
				//TODO:ここに処理を書く

				cmdexecute(i, c, player, anime);

				if (i == 999999) {
					a_bomb.playOneShot();
					changeScene(sstate::game, 5.0s);
				}
			}
		}
	}
	if (anime.nowanimationing && ((Scene::Time() - anime.begintime) / animeduration) > 1.0) {
		anime.nowanimationing = false;
	}

	for (int i = 0; i < c.pobjs.size(); i++) {
		complex dat;
		if (anime.nowanimationing) {
			dat = anime.from + (anime.to - anime.from) * ((Scene::Time() - anime.begintime) / animeduration);
		}
		else {
			dat = player.at.at;
		}
		if (c.pobjs[i].intersectsp(dat)) {
			switch (c.pobjs[i].type)
			{
			case pointobject::objtype::checkpoint:
				if (c.pobjs[i].value1 == POINTOBJECT_VALUE1_CHECKPOINT_UNCHECKED) {
					c.pobjs[i].value1 = POINTOBJECT_VALUE1_CHECKPOINT_CHECKED;
					c.checkdpointnum++;

					if (c.checkdpointnum >= c.allcheckpointnum) {
						a_kiraann.playOneShot();
					}
					else {
						a_pico.playOneShot();
					}
				}
				break;
			case pointobject::objtype::pstop:
			case pointobject::objtype::wstop:
				anime.nowanimationing = false;
				player.at.at = anime.bfrom;
				a_gusa.playOneShot();
				break;
			case pointobject::objtype::preset:
			case pointobject::objtype::wreset:
				a_gusa.playOneShot();
				changeScene(sstate::game, 3.0s);
				break;
			}
		}
	}
	if (!anime.nowanimationing) {
		if (c.goalpoint.insectsp(player.at.at)) {
			if (c.checkdpointnum >= c.allcheckpointnum) {
				Circle(Vec2{ player.at.at.real() * pmul + origin.x,(-player.at.at.imag()) * pmul + origin.y }, Periodic::Jump0_1(1s) * 2.0 + 12).drawFrame(2, Palette::Purple);////
				font(U"Press Enter!!!!").draw(20, player.at.at.real() * pmul + origin.x, (-player.at.at.imag()) * pmul + origin.y - 10, Palette::Seagreen.withAlpha(Periodic::Jump0_1(1s) * 256));


				if (KeyEnter.pressed()) {
					getData().coursenum++;
					a_changescene.playOneShot();

					if (!std::filesystem::exists(_path_course UR"({}.fgp)"_fmt(coursenum).toWstr())) {
						changeScene(sstate::clear, 3.1415s);
					}
					else {
						changeScene(sstate::game, 3.0s);
					}
				}
			}
		}
	}
}
void gamemgr::draw() const {
	// テキストを描く | Draw text
//	font(U"複素数平面移動ゲーム").draw(40, Vec2{ 20,  20 }, Palette::Black);
//	font(U"点P(α)をゴールまで移動させよう!!(やり直しはRキー)").draw(20, Vec2{ 20,80 }, Palette::Black);

	// X軸（横線）
	Line(origin.movedBy(-400, 0), origin.movedBy(400, 0)).draw(2, Palette::Red);
	font(U"Im").draw(20, Point{ origin.x + 2,2 }, Palette::Blue);

	// Y軸（縦線）
	Line(origin.movedBy(0, -300), origin.movedBy(0, 300)).draw(2, Palette::Blue);
	font(U"Re").draw(20, Point{ Scene::Width() - 28, origin.y - 23 }, Palette::Red);

	// 原点を強調
	Circle(origin, 5).draw(Palette::Purple);
	
	if (anime.nowanimationing) {
		player.Draw(anime);
	}
	else {
		player.Draw();
	}
	c.goalpoint.Draw(Palette::Gold,Palette::Black, c.allcheckpointnum <= c.checkdpointnum);

	for (int i = 0; i < c.pobjs.size(); i++) {
		c.pobjs[i].draw();
	}

	for (int i = 0; i < c.cmds.size(); i++) {
		c.cmds[i].draw(i);
	}

	if (getData().isRTA) {
		font(U"Time:{: .3f}"_fmt(Scene::Time() - getData().beginTime)).draw(fs+4 , Point{ 0,18 }, Palette::Black);
	}
}

void gamemgr::drawFadeIn(double t)const {
	draw();



	Circle{ origin.x, origin.y,500 }.drawFrame((1.0 - t) * 700.0, 0, Palette::Green);//.drawPie(360_deg * (t)+1_deg, ((1.0 - t) * 360.0_deg), Palette::Green);	//}

	font(U"STAGE {}"_fmt(getData().coursenum)).drawAt(Scene::Center(), Palette::Black.withA((1.0 - t) * 255));
	//Line(Vec2{ 0,0 }, Vec2{ (Scene::Width()),0 }).draw(14, Palette::White);
	//Line(Vec2{ 0,0 }, Vec2{ (Scene::Width()) * t,0 }).draw(14, Palette::Gold);
}

void gamemgr::drawFadeOut(double t)const {
	draw();
	Rect{ -10,-10,1000,1000 }.draw(Palette::Green.withAlpha(t * 255));
	///Line(Vec2{ 0,0 }, Vec2{ (Scene::Width()),0 }).draw(14, Palette::Gold);
	//Line(Vec2{ 0,0 }, Vec2{ (Scene::Width()) * t,0 }).draw(14, Palette::White);
	//font(U"congratulations!!").drawAt(Scene::Center(), Palette::Black.withA((1.0 - t) * 255));
}