/**
* @file clear.h
* クリアの実装を記述"src/seq/game/play.h"
* @details クリアの実装を記述
* @author YouTE
* @date 2019/05/07
*/
#pragma once

namespace sequence {
	namespace game {
		class Parent;
		class Clear {
		public:
			void Update(Parent*);///<更新
			void Draw();///<描画
		private:
			int counter_; ///<カウンター
			bool start_clear_flag_; ///クリアしたら数秒後セレクト画面に移行
		};
	}
}

