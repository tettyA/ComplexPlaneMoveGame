#include "stdafx.h"

#include "header.h"

#include "pointobject.h"

int pointobject::mouseOver() {
	auto at1 = Vec2{ p1.real() * pmul + origin.x,-p1.imag() * pmul + origin.y };
	auto at2 = Vec2{ p2.real() * pmul + origin.x,-p2.imag() * pmul + origin.y };

	if (Circle{ at1,cr + 10 }.mouseOver())return 1;
	if (Circle{ at2,cr + 10 }.mouseOver())return 2;
	return 0;
}

bool pointobject::intersectsp(complex pat) {
	auto at1 = Vec2{ p1.real() * pmul + origin.x,-p1.imag() * pmul + origin.y };
	auto at2 = Vec2{ p2.real() * pmul + origin.x,-p2.imag() * pmul + origin.y };

	Circle pc= Circle(Vec2{ pat.real() * pmul + origin.x,-pat.imag() * pmul + origin.y }, cr);

	switch (type)
	{
	case pointobject::objtype::wstop:
	case pointobject::objtype::wreset:
		if (Circle(at2, cr).intersects(pc))return true;
		if (Line{ at1,at2 }.intersects(pc))return true;

		__fallthrough;

	case pointobject::objtype::checkpoint:
	case pointobject::objtype::pstop:
	case pointobject::objtype::preset:
		if (Circle(at1, cr).intersects(pc))return true;
		break;
	}

	return false;
}

void pointobject::draw() const {
	auto at1 = Vec2{ p1.real() * pmul + origin.x,-p1.imag() * pmul + origin.y };
	auto at2 = Vec2{ p2.real() * pmul + origin.x,-p2.imag() * pmul + origin.y };

	switch (type)
	{
	case pointobject::objtype::checkpoint:
		if (value1 == POINTOBJECT_VALUE1_CHECKPOINT_CHECKED) {
			Rect{ Arg::center(Point{(int)p1.real() * pmul + origin.x,(int)-p1.imag() * pmul + origin.y}),10,10 }.rotated(45_deg).draw(Palette::Gray).drawFrame(1.0, Palette::Black);
		}
		else if (value1 == POINTOBJECT_VALUE1_CHECKPOINT_UNCHECKED) {
			Rect{ Arg::center(Point{(int)p1.real() * pmul + origin.x,(int)-p1.imag() * pmul + origin.y}),10,10 }.rotated(45_deg).drawFrame(1.0, Palette::Black);
		}
	
		break;
	case pointobject::objtype::pstop:
		Line{ at1.movedBy(-5,-5),at1.movedBy(5,5) }.draw(2.0, Palette::Black);
		Line{ at1.movedBy(-5,5),at1.movedBy(5,-5) }.draw(2.0, Palette::Black);
		break;
	case pointobject::objtype::wstop:
		Line{ at1.movedBy(-5,-5),at1.movedBy(5,5) }.draw(2.0, Palette::Black);
		Line{ at1.movedBy(-5,5),at1.movedBy(5,-5) }.draw(2.0, Palette::Black);
		Line{ at2.movedBy(-5,-5),at2.movedBy(5,5) }.draw(2.0, Palette::Black);
		Line{ at2.movedBy(-5,5),at2.movedBy(5,-5) }.draw(2.0, Palette::Black);
		Line{ at1,at2 }.draw(2.0, Palette::Black);
		break;
	case pointobject::objtype::preset:
		Line{ at1.movedBy(-5,-5),at1.movedBy(5,5) }.draw(2.0, Palette::Red);
		Line{ at1.movedBy(-5,5),at1.movedBy(5,-5) }.draw(2.0, Palette::Red);
		break;
	case pointobject::objtype::wreset:
		Line{ at1.movedBy(-5,-5),at1.movedBy(5,5) }.draw(2.0, Palette::Red);
		Line{ at1.movedBy(-5,5),at1.movedBy(5,-5) }.draw(2.0, Palette::Red);
		Line{ at2.movedBy(-5,-5),at2.movedBy(5,5) }.draw(2.0, Palette::Red);
		Line{ at2.movedBy(-5,5),at2.movedBy(5,-5) }.draw(2.0, Palette::Red);
		Line{ at1,at2 }.draw(2.0, Palette::Red);
		break;
	default:
		break;
	}
}
