/**
* @file loading.h
* ���[�f�B���O�̎������L�q"src/seq/game/loading.h"
* @details ���[�f�B���O�̎������L�q
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
			void Update(Parent* parent); ///<�X�V
			void Draw(); ///<�`��
		private:
			int counter_; ///<�J�E���^�[
			bool start_load_flag_; ///���[�h���n�܂������̃t���O

		};
	}
}
