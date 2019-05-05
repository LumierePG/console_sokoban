/**
* @file sokoban.h
* �Q�[���̒��g�̎����̋L�q"src/sokoban.h"
* @details �Q�[�����̂̎������s���@
* @author YouTE
* @date 2019/05/04
*/
#pragma once
#include <vector>
class Stage;
class Sokoban {
public:
	Sokoban(); ///<�R���X�g���N�^
	~Sokoban(); ///<�f�X�g���N�^
	void Init(); ///<����������
	void Init(int stage_number);///<�������̏��� �X�e�[�W�I��
	
	bool Update(); ///<�X�V
	void Draw(); ///<�`��
	bool Clear(); ///<�N���A�������ǂ����̔���
	
private:
	Stage* stage_; ///<�g�p����X�e�[�W�f�[�^
	Stage* stage_list_; ///�ǂݍ��񂾃X�e�[�W�f�[�^�Q�u����
	std::vector<std::string> map_name_list; ///<�X�e�[�W�I���̎���map��I�ׂ�悤�ɂ���

	bool MovablePushKey(char key, int* x_pos, int* y_pos); ///<�ړ�����������
	void SelectStage(int select_stage); ///�X�e�[�W��ύX����
};

//vector�ɃI�u�W�F�N�g���������Ă͂����Ȃ�