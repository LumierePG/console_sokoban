/**
* @file loading.h
* ローディングの実装を記述"src/seq/game/loading.h"
* @details ローディングの実装を記述
* @author YouTE
* @date 2019/05/07
*/
#pragma once

namespace sequence {
	namespace game {
		class Parent;
		class Loading {
		public:
			Loading();
			~Loading();
			void Update(Parent* parent); ///<更新
			void Draw(); ///<描画
		private:
			int counter_; ///<カウンター
			bool start_load_flag_; ///ロードが始まったかのフラグ

		};
	}
}
