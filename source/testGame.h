#pragma once

#include "header.h"

#ifdef VERSION_BETA


#include "stdafx.h"


#include "course.h"

#include "FileReadWriter.h"

#include "playerpoint.h"

#include "point.h"

#include <list>

#define path_koukaon UR"(.\System\koukaon\)"

class tgamemgr :public App::Scene
{
public:
	playerpoint player;
	int coursenum = 0;
	course c;
	tgamemgr(const InitData& init) :IScene{ init } {
		font = getData().font;
		coursenum = getData().coursenum;

		CourseLoader(c,_path_course UR"({}.fgp)"_fmt(coursenum));

		player.Setfont(font);
		c.goalpoint.Setfont(font);

		player.at.at = c.startpoint.at;
		player.at.textoffset = { -35,-24 };
		player.at.text = U"P(Éø)";

		anime = Moveanimation();

		a_kiraann = Audio(path_koukaon  U"kiran.mp3");
		a_changescene = Audio(path_koukaon  U"cs.mp3");
		a_bomb = Audio(path_koukaon U"bomb.mp3");
		a_gusa = Audio(path_koukaon  U"gusa.mp3");
		a_pico = Audio(path_koukaon U"pico.mp3");

		motofp=Window::GetTitle();
		if(motofp[0]!=U'T')
		Window::SetTitle(U"TEST(QÉLÅ[Ç≈èIóπ){}"_fmt(motofp));
	}
	void draw() const override;
	void update() override;
private:
	const Point origin = Scene::Center();
	String motofp;
	Font font;
	Audio a_kiraann;
	Audio a_changescene;
	Audio a_bomb;
	Audio a_gusa;
	Audio a_pico;
	//Audio a_bgm;
	Moveanimation anime;
	void drawFadeIn(double t)const override;
	void drawFadeOut(double t)const override;
};





#endif
