#include "title.h"
#include <iostream>
#include "parent.h"
#include "../key_manager.h"
namespace sequence {
	/**
	* �`�揈��
	* @details �^�C�g����ʂ̕`��
	*/
	void Title::Draw() {
		std::cout << "\
##########\n\
#        #\n\
# �q�ɔ� #\n\
#        #\n\
##########\n";
	}
	/**
	* �X�V
	* @param [out] parent �V�[�P���X�ړ��p
	*/
	void Title::Update(Parent* parent) {

		Draw();

		//�L�[���삪�X�e�[�W�I����ʂփV�[�����ڍs����
		char ch = KeyManager::GetInstance()->GetKey();

		if (ch) {
			parent->MoveTo(sequence::Parent::kSelectStage);
		}
		
	}
}