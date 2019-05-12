//#include "sokoban.h"
//#include <vector>
//#include <fstream>
//
//#include "file_manager.h"
//#include "key_manager.h"
//
//#include "state.h"
///**
//* �R���X�g���N�^
//*/
//Sokoban::Sokoban() {
//	stage_ = new State();
//}
///**
//* �f�X�g���N�^
//*/
//Sokoban::~Sokoban() {
//	delete stage_;
//	stage_ = nullptr;
//	//TODO:�z��̉���̌㏈�����킩���
//	delete[] stage_list_;
//	stage_list_ = nullptr;
//}
//
///**
//* ����������
//*/
//void Sokoban::Init() {
//	//�}�b�v�f�[�^�������ׂď���Ă�t�@�C����ǂݍ���
//	std::ifstream* fin;
//	fin = FileManager::GetInstance()->ReadFile("map/maplist.txt");
//
//	std::string ss;
//	///�ǂݍ��݂��Ǘ�����t���O
//	bool flag = false;
//	while (std::getline(*fin, ss)) {
//
//		///�}�b�v�̐���m�肽���̂ł����܂ŋ�ǂ�
//		if (ss.compare("@map_name") == 0) {
//			flag = true;
//			getline(*fin, ss); ///<���̍s�Ɉڍs
//		}
//		///�}�b�v�̐��̓ǂݍ��ݏW�I������
//		else if (ss.compare("@map_name_end") == 0) {
//			flag = false;
//			break;
//		}
//		//�}�b�v���̓ǂݍ���
//		if (flag) {
//			map_name_list.push_back(ss);
//			ss.erase(); ///<��ɂ���
//		}	
//	}
//	FileManager::GetInstance()->CloseFile(fin);
//
//	//�X�e�[�W�̐���0�ȊO�Ȃ�
//	int stage_num = static_cast<int>(map_name_list.size());
//
//	if (0 < stage_num) {
//		stage_list_ = new Stage[stage_num];
//
//		for (int index = 0; index < stage_num; ++index) {
//			stage_list_[index].Init(map_name_list.at(index));
//		}
//	}
//	//�X�e�[�W�I��������Ȃ��ꍇ�͍ŏ��̃X�e�[�W����
//	SelectStage(0);
//}
///**
//* ����������
//* @details �t�@�C���ǂݍ��݂����˂�����������
//* @param [in] select_stage �J�n����X�e�[�W
//*/
//void Sokoban::Init(int select_stage) {
//	//�}�b�v�f�[�^�������ׂď���Ă�t�@�C����ǂݍ���
//	std::ifstream* fin;
//	fin = FileManager::GetInstance()->ReadFile("map/maplist.txt");
//
//	std::string ss;
//	///�ǂݍ��݂��Ǘ�����t���O
//	bool flag = false;
//	while (std::getline(*fin, ss)) {
//
//		///�}�b�v�̐���m�肽���̂ł����܂ŋ�ǂ�
//		if (ss.compare("@map_name") == 0) {
//			flag = true;
//			getline(*fin, ss); ///<���̍s�Ɉڍs
//		}
//		///�}�b�v�̐��̓ǂݍ��ݏW�I������
//		else if (ss.compare("@map_name_end") == 0) {
//			flag = false;
//			break;
//		}
//		//�}�b�v���̓ǂݍ���
//		if (flag) {
//			map_name_list.push_back(ss);
//			ss.erase(); ///<��ɂ���
//		}
//	}
//	FileManager::GetInstance()->CloseFile(fin);
//
//	//�X�e�[�W�̐���0�ȊO�Ȃ�
//	int stage_num = static_cast<int>(map_name_list.size());
//
//	if (0 < stage_num) {
//		stage_list_ = new Stage[stage_num];
//
//		for (int index = 0; index < stage_num; ++index) {
//			stage_list_[index].Init(map_name_list.at(index));
//		}
//	}
//	//�����͈͂̃X�e�[�W��I��
//	if (select_stage <= stage_num) {
//		SelectStage(select_stage);
//	}
//}
///**
//* �`��
//*/
//void Sokoban::Draw() {
//	//�R���\�[����ʂ��N���A����
//	std::system("cls");
//	stage_->Draw();
//}
///**
//* �X�e�[�W��ύX���鏈��
//* @param [in] stage_number�@�ύX����X�e�[�W�ԍ�
//*/
//void Sokoban::SelectStage(int stage_number) {
//	*stage_ = stage_list_[stage_number];
//}
///**
//* �X�e�[�W���̍s�����X�V����@�Q�[����������
//*/
//bool Sokoban::Update() {
//	//�L�[����
//	char key = KeyManager::GetInstance()->GetKey();
//	//x��y���̈ړ�����
//	int difference_x, difference_y;
//	difference_x = difference_y = 0;
//	
//	bool flag = MovablePushKey(key, &difference_x, &difference_y);
//	if (!flag) {
//		return false; ///<�ړ��s�ŏ����𔲂���
//	}
//	//�l�̌��݈ʒu
//	int man_x_pos, man_y_pos;
//	flag = stage_->SearchMan(&man_x_pos, &man_y_pos);
//	if (!flag) {
//		return false; ///<�l�𔭌��ł��Ȃ������̂ŏ����𔲂���
//	}
//	//�ړ���̗\���̈ʒu
//	int expectation_man_x_pos = man_x_pos + difference_x;
//	int expectation_man_y_pos = man_y_pos + difference_y;
//	flag = stage_->CheckOutOfRange(expectation_man_x_pos, expectation_man_y_pos);
//	if (!flag) {
//		return false; ///<�ړ��悪�͈͊O�Ȃ珈���𔲂���
//	}
//	int move_pattern = stage_->CheckMovableMan(expectation_man_x_pos, expectation_man_y_pos,difference_x, difference_y);
//	if (move_pattern == -1) {
//		return false; ///<�ړ��悪�ړ��s�Ȃ珈���𔲂���
//	}
//	stage_->MoveObject(move_pattern,man_x_pos, man_y_pos,difference_x, difference_y);
//
//	return true; ///�X�V����
//}
///**
//* �ړ��\�ȏꏊ�ւ̃L�[�������ꂽ��
//* @param [in] key �L�[����
//* @param [out] *x_pos x���̈ړ�����
//* @param [out] *y_pos y���̈ړ�����
//*/
//bool Sokoban::MovablePushKey(char key, int* x_pos, int* y_pos) {
//	int difference_x, difference_y;
//	difference_x = difference_y = 0;
//	switch (key) {
//	case 'a':case 'A': --difference_x; break;
//	case 'd':case 'D': ++difference_x; break;
//	case 'w':case 'W': --difference_y; break;
//	case 's':case 'S': ++difference_y; break;
//	}
//
//	if (difference_x != 0 || difference_y != 0) {
//		*x_pos = difference_x;
//		*y_pos = difference_y;
//		return true;
//	}
//	return false;
//}
///**
//* �N���A�������ǂ����̔���
//* @retval true�@�N���A
//* @retval false ���N���A
//*/
//bool Sokoban::Clear() {
//	return stage_->Clear();
//}