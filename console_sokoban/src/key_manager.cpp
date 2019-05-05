#include "key_manager.h"
#include <iostream>
//�B��̃C���X�^���X
KeyManager* KeyManager::instance = nullptr;
/**
* �����̎n�܂�ɌĂ�
*/
void KeyManager::Create() {
	if (!instance) {
		instance = new KeyManager;
	}
}
/**
* �����̏I���ɌĂ�
*/
void KeyManager::Destory() {
	delete instance;
	instance = nullptr;
}
/**
* �C���X�^���X�̌Ăяo��
* @return �Ăяo���C���X�^���X��Ԃ�
*/
KeyManager* KeyManager::GetInstance() {
	return instance;
}
/**
* �L�[���͂̎擾
* @return �����ꂽ�L�[��Ԃ�
*/
char KeyManager::GetKey() {
	char ch;
	std::cin >> ch;
	return ch;
}