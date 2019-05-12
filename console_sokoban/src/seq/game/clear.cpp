#include "clear.h"
#include "parent.h"
#include <iostream>
namespace sequence {
	namespace game {
		/**
		* �X�V
		*/
		void Clear::Update(Parent* parent) {
			Draw();
			if (!start_clear_flag_) {
				parent->StartLoading();
				start_clear_flag_ = true;
			}
			++counter_;
			if (counter_ % 60 == 0) {
				parent->MoveTo(Parent::kStageSelect);
			}
		}
		/**
		* �`��
		*/
		void Clear::Draw() {
			std::system("cls");
			std::cout << "�N���A" << std::endl;
		}
	}
}