/**
* @file paly.h
* �Q�[�����s�̎������L�q"src/seq/game/play.h"
* @details �Q�[�����s�̎������L�q
* @author YouTE
* @date 2019/05/07
*/
#pragma once

namespace sequence {
	namespace game {
		class Parent;
		class Play {
		public:
			void Update(Parent* parent);///<�X�V
			void Draw(Parent* parent);///�`��
		private:
			bool MovablePushKey(char key, int* x_pos, int* y_pos);
		};
	}
}
