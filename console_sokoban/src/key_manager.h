/**
* @file key_manager.h
* �L�[�}�l�[�W���[�N���X�̋L�q"src/key_manager.h"
* @details �L�[����̓C���X�^���X��������������Ă�������g���@
* @author YouTE
* @date 2019/05/05
*/
#pragma once
#include <iostream>

class KeyManager{
public:
	static void Create(); ///<�����̎n�܂�ɌĂ�
	static void Destory(); ///<�����̏I���ɌĂ�
	static KeyManager* GetInstance(); ///<�L�[�C���X�^���X�Ăяo��

	char GetKey(); ///<�L�[���͂̎擾

private:
	static KeyManager* instance; ///<�B��̃C���X�^���X

	///�V���O���g��
	KeyManager() {};
	KeyManager(const KeyManager& obj) {};
	~KeyManager() {};
};
