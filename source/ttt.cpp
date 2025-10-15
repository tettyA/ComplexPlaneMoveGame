#include "Title.h"

void Title::draw() const{
	// テキストを描く | Draw text
	font(U"複素数平面上移動ゲーム").draw(40, Vec2{ 20,  20 }, Palette::Black);
	font(U"点P(α)をゴールまで移動させよう!!").draw(20, Vec2{ 20,80 }, Palette::Black);

	// X軸（横線）
	Line(origin.movedBy(-400, 0), origin.movedBy(400, 0)).draw(2, Palette::Red);
	font(U"Im").draw(20, Point{ origin.x + 2,2 }, Palette::Blue);

	// Y軸（縦線）
	Line(origin.movedBy(0, -300), origin.movedBy(0, 300)).draw(2, Palette::Blue);
	font(U"Re").draw(20, Point{ Scene::Width() - 28, origin.y - 23 }, Palette::Red);

	// 原点を強調
	Circle(origin, cr).draw(Palette::Purple);



	begingame.Draw(Palette::Green,Palette::Green.withAlpha(Periodic::Sawtooth0_1(0.9s)*256.0));


	{



		{
#ifdef VERSION_BETA
			if (beginRTA.at != player.at.at) {
				{
					const Vec2 center{ (beginRTA.at.real() * pmul + origin.x + beginRTA.textoffset.x) + 15
		, (-beginRTA.at.imag() * pmul + origin.y + beginRTA.textoffset.y) - 15 };

					const double angle = (Scene::Time() * 734_deg);
					const Transformer2D tr{ Mat3x2::Rotate(angle, center) };
					font(beginRTA.text).drawAt(fs, center, Palette::Blue.withAlpha(Periodic::Sawtooth0_1(0.25s) * 256.0));
				}
				Circle(Vec2{ beginRTA.at.real() * pmul + origin.x,-beginRTA.at.imag() * pmul + origin.y }, cr).draw(HSV(Periodic::Sawtooth0_1(0.3s) * 256.0));


			}
			else {
				font(beginRTA.text).draw(fs,Vec2{ (beginRTA.at.real() * pmul + origin.x + beginRTA.textoffset.x) + 15
			, (-beginRTA.at.imag() * pmul + origin.y + beginRTA.textoffset.y) - 15 }, Palette::Blue.withAlpha(Periodic::Sawtooth0_1(0.25s) * 256.0));

			}
#endif

		}


	}

#ifdef VERSION_BETA
	editgame.Draw();
#endif

	player.Draw();
	
}

void Title::update() {
	if (SimpleGUI::Button(U"+1", Vec2{ 638,510 })) player.at.at += 1;
	if (SimpleGUI::Button(U"-1", Vec2{ 700,510 })) player.at.at -= 1;
	if (SimpleGUI::Button(U"+i", Vec2{ 638,550 })) player.at.at += 1i;
	if (SimpleGUI::Button(U"-i", Vec2{ 700,550 })) player.at.at -= 1i;

	if (player.at.at == begingame.at) {
		Circle(Vec2{ player.at.at.real() * pmul + origin.x,(-player.at.at.imag()) * pmul + origin.y }, Periodic::Jump0_1(1s) * 2.0 + 12).drawFrame(2, Palette::Purple);////
		font(U"Press Enter!!!!").draw(20, player.at.at.real() * pmul + origin.x, (-player.at.at.imag()) * pmul + origin.y - 10, Palette::Seagreen.withAlpha(Periodic::Jump0_1(1s) * 256));


		if (KeyEnter.pressed()) {
			getData().coursenum = 1;
			getData().goal = complex(10, 10);
			getData().isRTA = false;

			changeScene(sstate::game, 3.0s);
		}
	}
#ifdef VERSION_BETA
	if (player.at.at == beginRTA.at) {
		Circle(Vec2{ player.at.at.real() * pmul + origin.x,(-player.at.at.imag()) * pmul + origin.y }, Periodic::Jump0_1(0.2s) * 3.50 + 12).drawFrame(2, HSV(Periodic::Sawtooth0_1(0.3s) * 256.0));////
		{
			const Vec2 center{ player.at.at.real() * pmul + origin.x, (-player.at.at.imag()) * pmul + origin.y - 10 };

			const Transformer2D tr{ Mat3x2::Rotate((Scene::Time() * 972_deg), center) };

			font(U"Press Enter!!!!").drawAt(20, center, Palette::Seagreen.withAlpha(Periodic::Jump0_1(1s) * 256));
		}

		if (KeyEnter.pressed()) {
			getData().coursenum = 1;
			getData().goal = complex(10, 10);
			getData().isRTA = true;
			getData().beginTime = Scene::Time();
			changeScene(sstate::game, 3.0s);
		}
	}
#endif
#ifdef VERSION_BETA
	if (player.at.at == editgame.at) {
		if (KeyEnter.pressed()) {
			changeScene(sstate::edit, 3.0s);
		}
	}
#endif
}


void Title::drawFadeOut(double t) const{
	draw();


	int repnum = 50;
	for (int i = 1; i <= (t > 0.5 ? 0.5 : t) * repnum; i++) {
		Circle{ player.at.at.real() * pmul + origin.x,-player.at.at.imag() * pmul + origin.y,i * 35 }.drawFrame(10,Palette::Green);
	}

	if (0.5 < t) {
		for (int i = 1; i <= repnum; i++) {
			Circle{ player.at.at.real() * pmul + origin.x,-player.at.at.imag() * pmul + origin.y,i * 35 }.drawArc(0_deg, 360_deg * ((t - 0.48) * 2.0), 35, 35, Palette::Green);
		}
	}

	Line(Vec2{ 0,0 }, Vec2{ (Scene::Width()),0 }).draw(14, Palette::Gold);
	Line(Vec2{ 0,0 }, Vec2{ (Scene::Width()) * t,0 }).draw(14, Palette::White);
}
