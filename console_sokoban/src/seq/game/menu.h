/**
* @file menu.h
* メニューの実装を記述"src/seq/game/play.h"
* @details メニューの実装を記述
* @author YouTE
* @date 2019/05/07
*/
#pragma once

namespace sequence {
	namespace game {
		class Parent;
		class Menu {
		public:
			void Update(Parent*);///<更新
			void Draw();///<描画
		private:
		};
	}
}

