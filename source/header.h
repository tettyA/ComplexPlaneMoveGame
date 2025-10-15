#pragma once
#define VERSION_BETA
//TODO:完成版をビルドすつ時はundefする。
#undef VERSION_BETA

#include "point.h"

#include "cmd.h"
#include <complex>

using complex = std::complex<double>;
using point = std::complex<double>;

//座標に掛ける倍率
#define pmul (10)
//点の描画半径
#define cr (5)
//フォントサイズ
#define fs (15)
enum class sstate {
	title, game,clear,
#ifdef VERSION_BETA
	edit,testgame
#endif
};
#ifdef VERSION_BETA
#define COURSENUM_TESTPLAY 999999
#endif

struct GameData {
	Font font;
	point start;
	point goal;
	int coursenum;
	bool isRTA;
	double beginTime;

};



using App = SceneManager<sstate,GameData>;


//3.1415926535897932384626433832795 / 180 
#define  _to_rad  *(0.01745329251994329576923690768489)

//1秒で移動
struct Moveanimation {
	double begintime;
	bool nowanimationing = false;
	complex from;
	complex to;
	complex bfrom;
};

constexpr double animeduration = 1.0;

#define _path_course UR"(.\System\Courses\)"
