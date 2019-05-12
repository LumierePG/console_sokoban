#include "loading.h"
#include <iostream>
#include "parent.h"
namespace sequence {
	namespace game {
		/**
		* �R���X�g���N�^
		*/
		Loading::Loading() 
			:counter_(0), start_load_flag_(false) {
		
		}
		/**
		* �f�X�g���N�^
		*/
		Loading::~Loading() {
		
		}
		/**
		* �X�V
		* @details sokoban��ǂݍ��ށ@�J�E���g�����Ĉ�莞�Ԍo�ƃQ�[����ʂֈڍs
		* @param [out] *parent ���̃V�[���Ɉړ��p
		*/
		void Loading::Update(Parent* parent) {
			Draw();
			if (!start_load_flag_) {		
				parent->StartLoading();
				start_load_flag_ = true;
			}
			++counter_;
			if (counter_ % 60 == 0) {
				parent->MoveTo(Parent::kPlay);
			}
		}
		/**
		* �`��
		*/
		void Loading::Draw() {
			std::system("cls");
			std::cout << "��`�ǒ�" << std::endl;
		}
	}
}