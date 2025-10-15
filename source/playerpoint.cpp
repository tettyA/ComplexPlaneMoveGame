#include "stdafx.h"
#include "playerpoint.h"

# include <Siv3D.hpp> 

void playerpoint::Draw() const {

	at.Draw();

	font(U"α = {: .5f}+ {: .5f}i"_fmt(at.at.real(), at.at.imag())).draw(fs + 3, Vec2{0,0}, Palette::Black);


	//playerとgoalが重なっているときに強調表示
	//if (at.at==goal) {
		//Circle(Vec2{ goal.real() * pmul + origin.x,(-goal.imag()) * pmul + origin.y }, Periodic::Jump0_1(1s) * 2.0 + 12).drawFrame(2, Palette::Purple);
	//}
}

void playerpoint::Draw(Moveanimation mav) const {
	if (!mav.nowanimationing)return;
	complex dat = mav.from + (mav.to - mav.from) * ((Scene::Time() - mav.begintime) / animeduration);
	font(at.text).draw(fs, Vec2{ dat.real() * pmul + origin.x + at.textoffset.x,-dat.imag() * pmul + origin.y + at.textoffset.y }, Palette::Black);
	Circle(Vec2{ dat.real() * pmul + origin.x,-dat.imag() * pmul + origin.y }, cr).draw(Palette::Black);
	font(U"α = {: .5f}+ {: .5f}i"_fmt(dat.real(), dat.imag())).draw(fs + 3, Vec2{ 0,0 }, Palette::Black);
}

void playerpoint::Update() {
/*	if (KeyR.down()) {
		at.at = 0;
	}*/
}
