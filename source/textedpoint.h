#pragma once

#include "header.h"

#include "point.h"
class textedpoint
{
public:
	inline void Setfont(Font& font) {
		this->font = font;
	}
	//点とテキスト描きます．
	void Draw(ColorF colp = Palette::Black, ColorF colstr = Palette::Black,bool isvalid=true) const;
	bool insectsp(complex pat);//移動中は判定しません。
	point at;
	String text;
	Point textoffset;
private:
	const Point origin = Scene::Center();
	Font font;

};

