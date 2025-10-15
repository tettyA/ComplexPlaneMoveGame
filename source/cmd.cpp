#include "stdafx.h"
#include "cmd.h"

bool cmd::MouseOver(int i) const{
	return RectF{ Scene::Rect().w - 200,i * 40 + 5,180,35 }.mouseOver();
}
void cmd::draw(int i) const {
	RectF{ Scene::Rect().w - 200,i * 40 + 5,180,35 }.draw( MouseOver(i)?Palette::Mediumpurple: Palette::Purple).drawFrame(2.0, Palette::Black);
	switch (cmdtype)
	{
	case cmd::type::addre:
		FontAsset(U"f")(U"+({})"_fmt(value1)).draw(20, Point{ Scene::Rect().w - 200,i * 40 + 8 });
		break;
	case cmd::type::addim:
		FontAsset(U"f")(U"+({}i)"_fmt(value1)).draw(20, Point{ Scene::Rect().w - 200,i * 40 + 8 });
		break;
	case cmd::type::adddeg:
		FontAsset(U"f")(U"*(cos({}°)+isin({}°))"_fmt(value1, value1)).draw(14, Point{ Scene::Rect().w - 200,i * 40 + 8 });
		break;
	case cmd::type::addr:
		FontAsset(U"f")(U"r+={}"_fmt(value1)).draw(20, Point{ Scene::Rect().w - 200,i * 40 + 8 });
		break;
	}

	if (nokori != cardinf) {
		FontAsset(U"f")(U"x{}"_fmt(nokori)).draw(15, Arg::topRight(Scene::Rect().w - 210, i * 40 + 18), Palette::Black);
	}
}
