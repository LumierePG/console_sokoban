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
class State {
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
	State(const std::string& stage_data); ///<�R���X�g���N�^
	State(const State& obj);///<�R�s�[�R���X�g���N�^
	State& operator=(const State& obj); ///<������Z�q
	~State(); ///<�f�X�g���N�^

	void Draw()const; ///<�X�e�[�W�̕`��

	void Reset(); ///������Ԃɖ߂�
	void SetSize(int* width, int* height);///�����Əc���̎擾


	void Update(int difference_x, int difference_y);///�X�V
	void SearchMan(int* x_pos, int* y_pos); ///<�l����̃f�[�^�̈ʒu��T��
	bool CheckOutOfRange(int x_pos, int y_pos)const; ///<�ړ��悪�͈͊O���`�F�b�N����
	int CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y)const;
	void MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y); ///<�����ɂ���čX�V�p�^�[����ς���
	bool SearchObject(Object obj)const; ///<�����̒T�������f�[�^����������
	bool Clear()const;///<�N���A�������̔���

private:
	Cell<Object>* objects_; ///cell�N���X�Ŕz����Ǘ�����
	std::string stage_data_; ///�X�e�[�W�f�[�^

	void SetStageData(); ///<�X�e�[�W�f�[�^��ݒ肷��

	void Draw_obj(Object obj) const; ///<�����ɍ��킹���I�u�W�F�N�g��`�悷��
};