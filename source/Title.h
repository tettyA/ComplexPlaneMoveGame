#pragma once
#include "stdafx.h"

#include "header.h"


#include "point.h"
#include "textedpoint.h"
#include "playerpoint.h"


class Title
	:public App::Scene
{
public:
	Title(const InitData& init) :IScene{ init } {
		font = Font{ FontMethod::MSDF, 48, Typeface::Bold };
		getData().font = font;
		getData().start = 0;
	
		player.at.at = 0;
		player.at.text = U"P(α)";
		player.at.textoffset = { -35,-24 };
		//player.goal =
	//		getData().goal = complex( 10000000,10000000 );
		player.Setfont(font);

		begingame.at = complex( 10 , 10);
		

		begingame.textoffset = { 5,5 };
		begingame.text = U"開始";

#ifdef VERSION_BETA
		beginRTA.Setfont(font);
		beginRTA.at = complex(5,15);
		beginRTA.textoffset = { 5,5 };
		beginRTA.text = U"RTA 開始";

		editgame.at = -1;
		editgame.text = U"編集";
		editgame.textoffset = { 5,5 };
		editgame.textoffset = { 5,5 };
		editgame.Setfont(font);
#endif
		begingame.Setfont(font);
		
	}
	void draw() const override;
	void update() override;

	playerpoint player;
	textedpoint begingame;

#ifdef VERSION_BETA
	textedpoint editgame;

	textedpoint beginRTA;
#endif
private:
	const Point origin = Scene::Center();
	Font font;

	void drawFadeOut(double t)const override;
};

