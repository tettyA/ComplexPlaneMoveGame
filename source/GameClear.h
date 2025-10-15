#pragma once
#include "stdafx.h"

#include "header.h"


#include "point.h"
#include "textedpoint.h"
#include "playerpoint.h"



class GameClear :public App::Scene
{
public:
    double ClearTime;
    GameClear(const InitData& init) :IScene{ init } {
        ClearTime = Scene::Time() - getData().beginTime;
        font = getData().font;
    }

    void draw() const override;
    void update() override;
private:
    Font font;
};

