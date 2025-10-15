#pragma once

#include "header.h"

#include "point.h"
#include "textedpoint.h"


class playerpoint
{
public:
	inline void Setfont(Font& font) {
		this->font = font;
		at.Setfont(font);
	}
	//プレイヤーの点を描きます．(Goal,Orginは描かない)
	void Draw() const;
	void Draw(Moveanimation mav)const;
	//プレイヤーの点に関する処理を行います．
	void Update();

	//void (point start, point goal);
	textedpoint at;
//	point goal;
private:
	const Point origin = Scene::Center();
	Font font;

};



