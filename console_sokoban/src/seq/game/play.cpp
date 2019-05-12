#include "play.h"
#include "parent.h"
#include "../../state.h"
#include "../../key_manager.h"
namespace sequence {
	namespace game {
		/**
		* 更新
		*/
		void Play::Update(Parent* parent) {
			State* state = parent->GetState();
			bool flag = false;

			flag = state->Clear();
			if (flag) {
				parent->MoveTo(Parent::kClear);
				return;
			}
			Draw(parent);

			//キー入力
			char key = KeyManager::GetInstance()->GetKey();
			//x軸y軸の移動差分
			int difference_x, difference_y;
			difference_x = difference_y = 0;
			
			flag = MovablePushKey(key, &difference_x, &difference_y);
			if (!flag) {
				return;///関数を抜ける
			}
			//更新
			state->Update(difference_x, difference_y);

			
		}
		/**
		* 描画
		*/
		void Play::Draw(Parent* parent) {
			State* state = parent->GetState();
			state->Draw();
		}
		/**
		* 移動可能な場所へのキーが押されたか
		* @param [in] key キー入力
		* @param [out] *x_pos x軸の移動差分
		* @param [out] *y_pos y軸の移動差分
		*/
		bool Play::MovablePushKey(char key, int* x_pos, int* y_pos) {
			int difference_x, difference_y;
				difference_x = difference_y = 0;
				switch (key) {
				case 'a':case 'A': --difference_x; break;
				case 'd':case 'D': ++difference_x; break;
				case 'w':case 'W': --difference_y; break;
				case 's':case 'S': ++difference_y; break;
				}
			
				if (difference_x != 0 || difference_y != 0) {
					*x_pos = difference_x;
					*y_pos = difference_y;
					return true;
				}
				return false;
		}
	}
}