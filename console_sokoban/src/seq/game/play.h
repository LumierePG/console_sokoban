/**
* @file paly.h
* ゲーム実行の実装を記述"src/seq/game/play.h"
* @details ゲーム実行の実装を記述
* @author YouTE
* @date 2019/05/07
*/
#pragma once

namespace sequence {
	namespace game {
		class Parent;
		class Play {
		public:
			void Update(Parent* parent);///<更新
			void Draw(Parent* parent);///描画
		private:
			bool MovablePushKey(char key, int* x_pos, int* y_pos);
		};
	}
}
