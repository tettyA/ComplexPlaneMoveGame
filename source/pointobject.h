#pragma once
#include "playerpoint.h"

#include "point.h"

#define POINTOBJECT_VALUE1_CHECKPOINT_UNCHECKED (0)
#define POINTOBJECT_VALUE1_CHECKPOINT_CHECKED (1)

//playerとgoal以外の物体を扱います．
class pointobject {
public:
	enum class objtype {
		checkpoint, pstop, wstop, preset, wreset
	};
	objtype type;
	int value1 = 0;
	point p1;
	point p2;
	Point origin = Scene::Center();

	void draw()const;
	//@brief マウスが交差しているかどうかを返します．
	//@return 0:交差していない.    1:p1と交差している    2:p2と交差している
	int mouseOver();

	bool intersectsp(complex pat);
};
