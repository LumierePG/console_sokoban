/**
* @file clear.h
* �N���A�̎������L�q"src/seq/game/play.h"
* @details �N���A�̎������L�q
* @author YouTE
* @date 2019/05/07
*/
#pragma once

namespace sequence {
	namespace game {
		class Parent;
		class Clear {
		public:
			void Update(Parent*);///<�X�V
			void Draw();///<�`��
		private:
			int counter_; ///<�J�E���^�[
			bool start_clear_flag_; ///�N���A�����琔�b��Z���N�g��ʂɈڍs
		};
	}
}

