#include "file_manager.h"
#include "game_lib.h"
#include <sstream>
#include <fstream>
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
* @details ��s���ǂݍ���œǂݍ��ݏI�������f�[�^�𓊂���
* @param [in] file_name �t�@�C����
* @return �ǂݍ��񂾃f�[�^��string�ŕԂ�
*/
const std::string FileManager::ReadFile(const std::string& file_directory) {

	std::ifstream fin(file_directory);
	
	if (!fin) {
		throw("�t�@�C�����ǂݍ��߂Ȃ��B");
	}
	std::stringstream stio;
	std::string ss;
	while (std::getline(fin,ss)) {
		stio << ss;
		ss.erase();
	}
	return stio.str();
}
/**
* �t�@�C���ǂݍ���
* @details ��s���ǂݍ���œǂݍ��ݏI�������f�[�^�𓊂���
* @param [in] file_name �t�@�C����
* @return �ǂݍ��񂾃f�[�^��string�ŕԂ�
*/
const std::string FileManager::ReadMapFile(const std::string& file_directory) {

	std::ifstream fin(file_directory);

	if (!fin) {
		throw("�t�@�C�����ǂݍ��߂Ȃ��B");
	}
	std::stringstream stio;
	std::string ss;
	while (std::getline(fin, ss)) {
		stio << ss << '\n';
		ss.erase();
	}
	return stio.str();
}
