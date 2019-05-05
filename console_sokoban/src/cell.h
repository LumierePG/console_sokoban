/**
* @file cell.h
* �Z���N���X�̋L�q "src/cell.h"
* @details Stage�N���X��cell�N���X����������ăX�e�[�W�f�[�^�Ƃ��Ďg��
* �����t���̃R���X�g���N�^�Ăяo���ȊO���̏��@�\���Ȃ��B
* @author YouTE
* @date 2019/05/03
*/
#pragma once
#include <vector>
template <typename T>class Cell{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	* @details �f�[�^�����o��width_,height_��0���������Ă����B<br>
	* �A�����̏������������ꍇ�̓f�[�^�����o���̂�0��������������ĂȂ��̂ŁA��������width_��height_��array_�������Ȃ���΂Ȃ�Ȃ�
 	*/
	Cell()
		: width_(0), height_(0){
		array_.resize(width_ * height_);
	}
	/**
	* �����t���R���X�g���N�^
	* @param [in] arg_width �f�[�^�����o��width_�̏�����
	* @param [in] arg_height �f�[�^�����o��height_�̏�����
	*/
	Cell(int arg_width, int arg_height) 
		: width_(arg_width), height_(arg_height){
		array_.resize(width_ * height_);
	}
	/**
	* array_��������x_pos,y_pos�̈ʒu���g���čX�V����
	* @param [in] x_pos ���̈ʒu
	* @param [in] y_pos �c�̈ʒu
	* @param [in] data �X�V����f�[�^
	* @retval true �L���ȃC���f�b�N�X���w��
	* @retval false �����ȃC���f�b�N�X���w��
	*/
	bool Add(int x_pos, int y_pos, T data) {
		if (0 <= (x_pos + y_pos * width_) &&
			(x_pos + y_pos * width_) < static_cast<int>(array_.size())) {
			array_.at(x_pos + y_pos * width_) = data;
			return true;
		}
		return false;
	}
	/**
	* array_��������pos�̈ʒu���g���čX�V����
	* @param [in] pos �X�V�������C���f�b�N�X
	* @param [in] data �X�V����f�[�^
	* @retval true �L���ȃC���f�b�N�X���w��
	* @retval false �����ȃC���f�b�N�X���w��
	*/
	bool Add(int pos, T data) {
		if (0 <= (pos) &&
			pos < static_cast<int>(array_.size())) {
			array_.at(pos) = data;
			return true;
		}
		return false;
	}
	/**
	* �����̎擾
	* @return width_ ����
	*/
	int GetWidth() {
		return width_;
	}
	/**
	* �c���̎擾
	* @return height_ �c��
	*/
	int GetHeight() {
		return height_;
	}
	/**
	* �����̐ݒ�
	* @param [in] arg_width �����o��width_���X�V
	*/
	void SetWidth(int arg_width) {
		width_ = arg_width;
	}
	/**
	* �c���̐ݒ�
	* @param [in] arg_height �����o��height_���X�V
	*/
	void SetHeight(int arg_height) {
		height_ = arg_height;
	}
	/**
	* �f�[�^�̃����o�̃��T�C�Y
	* @param [in] size ���T�C�Y�̑傫��
	*/
	void ArrayReSize(int size){
		array_.resize(size);
	}
	/**
	* �����₷���悤�ɉ��Z�q�̃I�[�o�[���[�h���쐬
	* @details �͈͊O���w�������ł���׎g�����ɒ���
	* TODO:expection������ǉ��\��
	* @param [in] x_pos ���̈ʒu
	* @param [in] y_pos �c�̈ʒu
	* @return �ύX�s�\�ȃf�[�^��Ԃ�
	*/
	const T& operator()(int x_pos, int y_pos) const{
		return array_.at(x_pos + y_pos * width_);
	}
	/**
	* �����₷���悤�ɉ��Z�q�̃I�[�o�[���[�h���쐬
	* @details �͈͊O���w�������ł���׎g�����ɒ���
	* @param [in] x_pos ���̈ʒu
	* @param [in] y_pos �c�̈ʒu
	* @return �ύX�\�ȃf�[�^��Ԃ�
	*/
	T& operator()(int x_pos, int y_pos) {
		return array_.at(x_pos + y_pos * width_);
	}

private:
	std::vector<T> array_; ///<�X�e�[�W�f�[�^
	int width_; ///<����
	int height_; ///<�c��
};