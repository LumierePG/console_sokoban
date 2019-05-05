/**
* @file file_manager.h
* �t�@�C���}�l�[�W���[�N���X�̋L�q"src/file_manager.h"
* @details �t�@�C���̈����̓C���X�^���X��������������Ă�������g�p
* @author YouTE
* @date 2019/05/02
*/
#pragma once
#include <fstream>
#include <string>

class FileManager {
public:
	static void Create(); ///<�����̎n�܂�ɌĂ�
	static void Destory(); ///<�����̏I���ɌĂ�
	static FileManager* GetInstance(); ///<�t�@�C���}�l�[�W���[�N���X�ɃA�N�Z�X����B��̊֐�

	std::ifstream* ReadFile(std::string file_name);///<�t�@�C����ǂݍ���
	void CloseFile(std::ifstream* file_name);///<ReadFIle��ǂ񂾌�K���ĂԎ�
private:
	static FileManager* instance; ///<�B��̃C���X�^���X
	///�V���O���g��
	FileManager() {};
	FileManager(const FileManager& obj) {};
	~FileManager() {};
};
