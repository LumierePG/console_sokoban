#include "stage.h"
#include "file_manager.h"
#include <sstream>
#include <algorithm>
#include <iostream>
/**
* �R���X�g���N�^
*/
Stage::Stage() 
	:stage_data_(nullptr){

}
/**
* �R�s�[�R���X�g���N�^
*/
Stage::Stage(const Stage& obj) {

	int width = obj.stage_data_->GetWidth();
	int height = obj.stage_data_->GetHeight();
	stage_data_ = new Cell<Object>(width, height);

	stage_data_->SetWidth(width);
	stage_data_->SetHeight(height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object o = obj.stage_data_->operator()(x, y);
			stage_data_->Add(x, y, o);
		}
	}
}
/**
* ������Z�q
*/
Stage& Stage::operator=(const Stage& obj) {
	//���ȑ���֎~
	if (this != &obj) {
		delete stage_data_;
		stage_data_ = nullptr;


		int width = obj.stage_data_->GetWidth();
		int height = obj.stage_data_->GetHeight();
		stage_data_ = new Cell<Object>(width,height);
		
		stage_data_->SetWidth(width);
		stage_data_->SetHeight(height);

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Object o = obj.stage_data_->operator()(x,y);
				stage_data_->Add(x, y, o);
			}
		}
	}
	return *this;
}
/**
* �f�X�g���N�^
*/
Stage::~Stage() {
	delete stage_data_;
	stage_data_ = nullptr;
}
/**
* �ǂݍ��񂾃t�@�C������cell�f�[�^������
* @param [in] map_name �}�b�v��
* @retval true �X�e�[�W�f�[�^�̍쐬����
* @retval false �������̎��_�Ŏ��s
*/
bool Stage::Init(const std::string& map_name) {

	std::stringstream file_name;
	file_name << "map/";
	file_name << map_name;
	std::ifstream* fin;
	fin = FileManager::GetInstance()->ReadFile(file_name.str());

	std::stringstream stio;
	std::string ss;

	while (getline(*fin,ss)) {
		stio << ss;
		///�s�̏I���ɂ킩��₷�����s�R�[�h��ǉ�
		stio << '\n';
		ss.erase();
	}
	std::string map_data = stio.str();
	int width, height;

	bool flag;
	flag = SetWidthHeight(map_data, &width, &height);
	///�����Əc�����擾�o���Ȃ������珉�������s����
	if (!flag) {
		return false;
	}
	stage_data_ = new Cell<Object>(width, height);
	SetStageData(map_data, stage_data_);
	
	return true;
}
/**
* ���c�̎擾
* @param [in] stage_data �t�@�C������ǂݍ��񂾃f�[�^
* @param [out] *width ����
* @param [out] *height �c��
* @retval true �擾����
* @retval false �擾���s
*/
bool Stage::SetWidthHeight(const std::string& map_data, int* width, int* height) {
	int x, y;
	int max_width, max_height;
	x = y = max_width = max_height = 0;
	
	for (auto t : map_data) {
		switch (t) {
		case '#':case ' ':case '.':
		case 'p':case 'P':case 'o':case 'O':
			++x;
			break;
		case '\n':
			++y;
			max_width	= std::max(x, max_width);
			max_height = std::max(y, max_height);
			x = 0;
			break;
		}
	}
	if (max_width != 0 || max_height != 0) {
		*width = max_width;
		*height = max_height;
		return true;
	}
	return false;
}
/**
* �X�e�[�W�f�[�^��ݒ�
* @param [in] map_data ���̃f�[�^�����ɃX�e�[�W�f�[�^���쐬
* @param [out] stage_data �V�K�쐬����X�e�[�W�f�[�^
*/
void Stage::SetStageData(const std::string& map_data, Cell<Object>* stage_data) {

	int index = 0;
	Object obj;

	for (auto t : map_data) {
		switch (t) {
		case '#': obj = kWall; break;
		case ' ': obj = kSpace; break;
		case '.': obj = kGoal; break;
		case 'p': obj = kMan; break;
		case 'P': obj = kManOnGoal; break;
		case 'o': obj = kBaggage; break;
		case 'O': obj = kBaggageOnGoal; break;

		default: obj = kUnknown; break;

		}
		if (obj != kUnknown) {
			stage_data->Add(index, obj);
			++index;
		}	
	}
}
/**
* �`��
*/
void Stage::Draw() {
	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Draw_obj((*stage_data_)(x,y));
		}
		std::cout << std::endl;
	}
}
/**
* �����ɍ��킹���I�u�W�F�N�g��`�悷��
* @detail Draw()�Ŏg�p����
* @param [in] index �I�u�W�F�N�g��index����ɂ��ĕ\��
*/
void Stage::Draw_obj(Object index) {
	char data[] = {'#', ' ', '.', 'p', 'P', 'o', 'O'};
	std::cout << data[index];
}
/**
* �l����̃f�[�^��T��
* @param [out] *x_pos x���ʒu
* @param [out] *y_pos y���ʒu
* @retval true ��������
* @retval false�@������Ȃ�
*/
bool Stage::SearchMan(int* x_pos, int* y_pos) {

	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*stage_data_)(x, y) == kMan ||
				(*stage_data_)(x, y) == kManOnGoal) {
				*x_pos = x;
				*y_pos = y;
				return true;
			}
		}
	}
	return false;
}
/**
* �ړ��悪�͈͊O���`�F�b�N����
* @param [in] x_pos x���̐l�̈ʒu
* @param [in] y_pos y���̐l�̈ʒu
* @retval true �͈͓�
* @retval false �͈͊O
*/
bool Stage::CheckOutOfRange(int x_pos, int y_pos) {
	
	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	///�}�b�v�O�Ɉʒu���ĂȂ�������
	if (0 <= x_pos &&
		x_pos < width &&
		0 < y_pos &&
		y_pos < height) {
		return true;
	}
	return false;
}
/**
* �ړ��悪�ړ��\���̃`�F�b�N����
* @details �ړ��悪�ړ��\���̃`�F�b�N���ĉו����������ꍇ�͍X�ɂ��̐���ړ��\���`�F�b�N����
* @param [in] expectation_man_x_pos x���̈ړ��̗\�z��
* @param [in] expectation_man_y_pos y���̈ړ��̗\�z��
* @param [in] difference_x x���̈ړ������@�ړ��悪�ړ��\�ȏꍇ������ׂ�וK�v
* @param [in] difference_y y���̈ړ�����
* @retval 0 �ړ��\ �p�^�[��1 �ړ��悪�����ړ��\�ȏꍇ
* @retval 1 �ړ��\ �p�^�[��2 �ړ���ɉו������݂��邪���̐���ړ��\�ȏꍇ
* @retval -1 �ړ��s��
*/
int Stage::CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y) {
	
	//�ړ��悪�ړ��\���`�F�b�N
	if ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggage ||
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) {
		///�X�ɗ\�z�̈ʒu
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		//�ēx�}�b�v���̔���
		bool flag = CheckOutOfRange(next_exprection_man_x_pos, next_exprection_man_y_pos);
		if (!flag) {
			return -1;
		}
		//�X�ɐ�̈ړ��悪�ړ��\���`�F�b�N
		if ((*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal ||
			(*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kSpace) {
			return 1;
		}
	}
	else if ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal || 
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kSpace) {
		return 0;
	}
	return -1;
}
/**
* �X�e�[�W��̃I�u�W�F�N�g�ɍX�V��������
* @details 
* @param [in] pattern �X�V�̎��
* @param [in] man_x_pos x���̐l�̈ʒu
* @param [in] max_y_pos y���̐l�̈ʒu
* @param [in] difference_x x���̈ړ�����
* @param [in] difference_y y���̈ړ�����
*/
void Stage::MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y) {
	int expectation_man_x_pos = man_x_pos + difference_x;
	int expectation_man_y_pos = man_y_pos + difference_y;
	switch (pattern) {
	case 0: ///�ړ��悪�S�[�����̓X�y�[�X�������ꍇ
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) = ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal) ? kManOnGoal : kMan;
		(*stage_data_)(man_x_pos, man_y_pos) = ((*stage_data_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
		break;
	case 1: ///<�ړ��悪�ו��ōX�ɐ悪�S�[�����̓X�y�[�X�������ꍇ
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		(*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) = ((*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal) ? kBaggageOnGoal : kBaggage;
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) = ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) ? kManOnGoal : kMan;
		(*stage_data_)(man_x_pos, man_y_pos) = ((*stage_data_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
	}
}
/**
* �����̒T�������f�[�^����������
* @param [in] �T�������X�e�[�W�f�[�^
* @retval true �f�[�^�𔭌�
* @retval false �f�[�^�𖢔���
*/
bool Stage::SearchObject(Object obj) {
	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*stage_data_)(x, y) == obj) {
				return true;
			}
		}
	}
	return false;
}
/**
* �N���A�������̔���
* @retval �N���A����
* @retval ���N���A
*/
bool Stage::Clear() {
	bool flag = SearchObject(kBaggage);
	///�f�[�^�𖢔����̏ꍇ�̓N���A
	if (!flag) { 
		return true;
	}
	///�f�[�^�𔭌��̏ꍇ�͖��N���A
	return false;
}