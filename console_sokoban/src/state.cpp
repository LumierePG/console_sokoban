#include "state.h"
#include "game_lib.h" ///
#include "file_manager.h"
#include <sstream>
#include <algorithm>
#include <iostream>

/**
* �R���X�g���N�^
* @param [in] map_name �}�b�v��
*/
State::State(const std::string& stage_data)
	:objects_(nullptr){

	stage_data_ = stage_data;
	//�f�[�^�I�[�ɉ��s��NULL�I�[�̒ǉ�
	//stage_data_.append("\n\0");
	//Reset�ŉ��c���͂킩��̂Ńf�t�H�Ă�
	objects_ = new Cell<Object>();
	//�ǂݍ��񂾃f�[�^���珉������������
	Reset();

}
/**
* �R�s�[�R���X�g���N�^
*/
State::State(const State& obj) {

	int width = obj.objects_->GetWidth();
	int height = obj.objects_->GetHeight();
	objects_ = new Cell<Object>(width, height);

	objects_->SetSize(width, height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object o = obj.objects_->operator()(x, y);
			(*objects_)(x,y) = o;
		}
	}
}
/**
* ������Z�q
*/
State& State::operator=(const State& obj) {
	//���ȑ���֎~
	if (this != &obj) {
		SAFE_DELETE(objects_);
		int width = obj.objects_->GetWidth();
		int height = obj.objects_->GetHeight();
		objects_ = new Cell<Object>(width,height);
		
		objects_->SetSize(width, height);

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Object o = obj.objects_->operator()(x, y);
				(*objects_)(x, y) = o;
			}
		}
	}
	return *this;
}
/**
* �f�X�g���N�^
*/
State::~State() {
	SAFE_DELETE(objects_);
}
/**
* ������Ԃɖ߂�
* 
*/
void State::Reset() {
	//�����Əc����ǂݍ��񂾃t�@�C���f�[�^����Z�b�g
	int width, height;
	SetSize(&width,&height);
	//�X�e�[�W�̃T�C�Y�Əc�����̃Z�b�g
	objects_->SetSize(width, height);
	//�X�e�[�W���Z�b�g
	SetStageData();
}
/**
* �����Əc�����}�b�v�f�[�^����擾
* @param [in] map_data �}�b�v�f�[�^
* @param [out] *width ����
* @param [out] *height �c��
*/
void State::SetSize(int* width, int* height) {
	int x, y;
	int max_width, max_height;
	x = y = max_width = max_height = 0;

	for (auto t : stage_data_) {
		switch (t) {
		case '#':case ' ':case '.':
		case 'p':case 'P':case 'o':case 'O':
			++x;
			break;
		case '\n':
			++y;
			//�ő�l�X�V
			max_width = std::max(x, max_width);
			max_height = std::max(y, max_height);
			x = 0;
			break;
		}
	}
	if (max_width == 0 || max_height == 0) {
		throw("�}�b�v�f�[�^�����Ă܂��B");
	}
	else {
		*width = max_width;
		*height = max_height;
	}
}
/**
* �X�e�[�W�f�[�^��ݒ�
* @param [in] map_data ���̃f�[�^�����ɃX�e�[�W�f�[�^���쐬
* @param [out] stage_data �V�K�쐬����X�e�[�W�f�[�^
*/
void State::SetStageData() {

	int index = 0;
	Object obj;

	for (auto t : stage_data_) {
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
			(*objects_)(index) = obj;
			++index;
		}	
	}
}
/**
* �`��
*/
void State::Draw() const {
	std::system("cls");
	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Draw_obj((*objects_)(x,y));
		}
		std::cout << std::endl;
	}
}
/**
* �����ɍ��킹���I�u�W�F�N�g��`�悷��
* @detail Draw()�Ŏg�p����
* @param [in] index �I�u�W�F�N�g��index����ɂ��ĕ\��
*/
void State::Draw_obj(Object index) const {
	char data[] = {'#', ' ', '.', 'p', 'P', 'o', 'O'};
	std::cout << data[index];
}
/**
* �l����̃f�[�^��T��
* @param [out] *x_pos x���ʒu
* @param [out] *y_pos y���ʒu
*/
void State::SearchMan(int* x_pos, int* y_pos) {

	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*objects_)(x, y) == kMan ||
				(*objects_)(x, y) == kManOnGoal) {
				*x_pos = x;
				*y_pos = y;
				return;
			}
		}
	}
	throw("��l������������Ȃ��B���蓾�Ȃ�");
}
/**
* �ړ��悪�͈͊O���`�F�b�N����
* @param [in] x_pos x���̐l�̈ʒu
* @param [in] y_pos y���̐l�̈ʒu
* @retval true �͈͓�
* @retval false �͈͊O
*/
bool State::CheckOutOfRange(int x_pos, int y_pos) const{
	
	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
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
int State::CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y) const{
	
	//�ړ��悪�ړ��\���`�F�b�N
	if ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggage ||
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) {
		///�X�ɗ\�z�̈ʒu
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		//�ēx�}�b�v���̔���
		bool flag = CheckOutOfRange(next_exprection_man_x_pos, next_exprection_man_y_pos);
		if (!flag) {
			return -1;
		}
		//�X�ɐ�̈ړ��悪�ړ��\���`�F�b�N
		if ((*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal ||
			(*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kSpace) {
			return 1;
		}
	}
	else if ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal ||
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kSpace) {
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
void State::MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y) {
	int expectation_man_x_pos = man_x_pos + difference_x;
	int expectation_man_y_pos = man_y_pos + difference_y;
	switch (pattern) {
	case 0: ///�ړ��悪�S�[�����̓X�y�[�X�������ꍇ
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) = ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal) ? kManOnGoal : kMan;
		(*objects_)(man_x_pos, man_y_pos) = ((*objects_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
		break;
	case 1: ///<�ړ��悪�ו��ōX�ɐ悪�S�[�����̓X�y�[�X�������ꍇ
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		(*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) = ((*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal) ? kBaggageOnGoal : kBaggage;
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) = ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) ? kManOnGoal : kMan;
		(*objects_)(man_x_pos, man_y_pos) = ((*objects_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
	}
}
/**
* �����̒T�������f�[�^����������
* @param [in] �T�������X�e�[�W�f�[�^
* @retval true �f�[�^�𔭌�
* @retval false �f�[�^�𖢔���
*/
bool State::SearchObject(Object obj) const{
	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*objects_)(x, y) == obj) {
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
bool State::Clear() const{
	bool flag = SearchObject(kBaggage);
	///�f�[�^�𖢔����̏ꍇ�̓N���A
	if (!flag) { 
		return true;
	}
	///�f�[�^�𔭌��̏ꍇ�͖��N���A
	return false;
}
/**
* �ړ�����`�F�b�N���ĉ\�Ȃ�I�u�W�F�N�g���X�V
* @param [in] difference_x x����
* @param [in] difference_y y����
*/
void State::Update(int difference_x, int difference_y) {
	//�l�̌��݈ʒu
	int man_x_pos, man_y_pos;
	SearchMan(&man_x_pos, &man_y_pos);

	//�ړ���̗\���̈ʒu
	int expectation_man_x_pos = man_x_pos + difference_x;
	int expectation_man_y_pos = man_y_pos + difference_y;
	bool flag = CheckOutOfRange(expectation_man_x_pos, expectation_man_y_pos);
	if (!flag) {
		return; ///<�ړ��悪�͈͊O�Ȃ珈���𔲂���
	}
	int move_pattern = CheckMovableMan(expectation_man_x_pos, expectation_man_y_pos, difference_x, difference_y);
	if (move_pattern == -1) {
		return; ///<�ړ��悪�ړ��s�Ȃ珈���𔲂���
	}
	MoveObject(move_pattern, man_x_pos, man_y_pos, difference_x, difference_y);
}