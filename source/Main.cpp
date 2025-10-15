# include <Siv3D.hpp> // OpenSiv3D v0.6.8

#include "header.h"

#include "Title.h"

#include "gamemgr.h"

#include "GameClear.h"

#ifdef VERSION_BETA
#include "sEdit.h"
#include "testGame.h"
#endif

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ Palette::White });

	FontAsset::Register(U"f", FontMethod::MSDF, 48, Typeface::Bold);
	Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	App mgr;
	mgr.add<Title>(sstate::title);
	mgr.add<gamemgr>(sstate::game);
	mgr.add<GameClear>(sstate::clear);
#ifdef VERSION_BETA
	mgr.add<sEdit>(sstate::edit);
	mgr.add<tgamemgr>(sstate::testgame);
#endif
	Audio a_bgm = Audio(path_koukaon U"hirusagarinooatu.mp3", Loop::Yes);

	a_bgm.play();

	while (System::Update())
	{


		if (not mgr.update()) {
			break;
		}


	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
