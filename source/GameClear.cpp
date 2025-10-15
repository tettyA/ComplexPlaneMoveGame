#include "stdafx.h"
#include "GameClear.h"


void GameClear::draw()const{
    font(U"CLEAR TIME:{: .3f}"_fmt(ClearTime)).drawAt(Scene::Center(), Palette::Black);
    font(U"タイトルに戻るにはEnterを押す。").draw(Point{ 0,0 },Palette::Black);
}

void GameClear::update() {
    if (KeyEnter.pressed()) {
        changeScene(sstate::title, 2.0s);
    }
}

