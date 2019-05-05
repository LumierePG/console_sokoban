#include "file_manager.h"
//�B��̃C���X�^���X
FileManager* FileManager::instance = nullptr;
/**
* �����̎n�܂�ɌĂ�
*/
void FileManager::Create() {
	if (!instance) {
		instance = new FileManager;
	}
}
/**
* �����̏I���ɌĂ�
*/
void FileManager::Destory() {
	delete instance;
	instance = nullptr;
}
/**
* �C���X�^���X�̌Ăяo��
* @return �Ăяo���C���X�^���X��Ԃ�
*/
FileManager* FileManager::GetInstance() {
	return instance;
}
/**
* �t�@�C���ǂݍ���
* @details new������͌Ă񂾐�ŏ�������
* @param [in] file_name �t�@�C����
* @return new�����t�@�C���|�C���^��Ԃ�
*/
std::ifstream* FileManager::ReadFile(std::string file_name) {
	std::ifstream* fin = new std::ifstream;
	fin->open(file_name);
	return fin;
}
/**
* �ǂݍ���ō�Ƃ�������K���Ă�
* @param [out] *fin �������new���ꂽ�t�@�C���|�C���^
* @details new�����f�[�^���폜���邽�߁AReadFile��ǂ񂾌�A�������I�������K���ĂԁB
*/
void FileManager::CloseFile(std::ifstream* fin) {
	fin->close();
	delete fin;
	fin = nullptr;
}