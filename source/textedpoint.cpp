#include "stdafx.h"
#include "textedpoint.h"

void textedpoint::Draw(ColorF colp,ColorF colstr,bool isvalid) const{
	
	font(text).draw(fs, Vec2{ at.real() * pmul + origin.x+textoffset.x,-at.imag() * pmul + origin.y +textoffset.y }, colstr);
	if (isvalid) {
		Circle(Vec2{ at.real() * pmul + origin.x,-at.imag() * pmul + origin.y }, cr).draw(colp);
	}
	else {
		Circle(Vec2{ at.real() * pmul + origin.x,-at.imag() * pmul + origin.y }, cr).drawFrame(1.0, colp);
	}
}

bool textedpoint::insectsp(complex pat) {
	Circle pc = Circle(Vec2{ pat.real() * pmul + origin.x,-pat.imag() * pmul + origin.y }, cr);
	Circle me=Circle(Vec2{ at.real() * pmul + origin.x,-at.imag() * pmul + origin.y }, cr);
	return pc.intersects(me);
}
