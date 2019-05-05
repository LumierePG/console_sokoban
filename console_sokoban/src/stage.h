/**
* @file stage.h
* @brief �X�e�[�W�������N���X
* @author YouTE
* @date 2019/05/03
*/
#pragma once
#include "cell.h"
#include <string>
/**
* @class �X�e�[�W�������N���X "src/stage.h"
* �X�e�[�W�֘A�͂����ň���
*/
class Stage {
private:
	///<�X�e�[�W�f�[�^
	enum Object {
		kWall,			///<'#'��
		kSpace,			///<' '��
		kGoal,			///<'.'�S�[��
		kMan,			///<'p'�l
		kManOnGoal,		///<'P'�S�[����̐l
		kBaggage,		///<'o'�ו�
		kBaggageOnGoal,	///<'O'�S�[����̉ו�

		kUnknown,		///<'?'����ȊO�̃f�[�^
	};
public:
	Stage(); ///<�R���X�g���N�^
	Stage(const Stage& obj);///<�R�s�[�R���X�g���N�^
	Stage& operator=(const Stage& obj); ///<������Z�q
	~Stage(); ///<�f�X�g���N�^
	bool Init(const std::string& map_name); ///<������

	void Draw(); ///<�X�e�[�W�̕`��

	bool SearchMan(int* x_pos, int* y_pos); ///<�l����̃f�[�^�̈ʒu��T��
	bool CheckOutOfRange(int x_pos, int y_pos); ///<�ړ��悪�͈͊O���`�F�b�N����
	int CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y);
	void MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y); ///<�����ɂ���čX�V�p�^�[����ς���
	bool SearchObject(Object obj); ///<�����̒T�������f�[�^����������
	bool Clear();///<�N���A�������̔���

	
private:
	Cell<Object>* stage_data_; ///<cell�N���X�Ŕz����Ǘ�����

	bool SetWidthHeight(const std::string& map_data, int* width, int* height); ///<���c�����擾����
	void SetStageData(const std::string& map_data, Cell<Object>* cell); ///<�X�e�[�W�f�[�^��ݒ肷��

	void Draw_obj(Object obj); ///<�����ɍ��킹���I�u�W�F�N�g��`�悷��
};