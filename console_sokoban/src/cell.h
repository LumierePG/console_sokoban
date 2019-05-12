#ifndef INCLUDED_CELL_H
#define INCLUDED_CELL_H
/**
* @file cell.h
* �Z���N���X�̋L�q "src/cell.h"
* @details Stage�N���X��cell�N���X����������ăX�e�[�W�f�[�^�Ƃ��Ďg��
* �����t���̃R���X�g���N�^�Ăяo���ȊO���̏��@�\���Ȃ��B
* @author YouTE
* @date 2019/05/03
*/

#include <vector>
#include "game_lib.h"
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
	* �V���������Əc���� array_�z��̃��T�C�Y
	* @param [in] arg_width
	* @param [in] arg_height
	*/
	void SetSize(int arg_width, int arg_height) {
		width_ = arg_width;
		height_ = arg_height;
		array_.resize(width_ * height_);
	}
	/**
	* �����̎擾
	* @return width_ ����
	*/
	int GetWidth() const{
		return width_;
	}
	/**
	* �c���̎擾
	* @return height_ �c��
	*/
	int GetHeight() const{
		return height_;
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
		if (0 > (x_pos + y_pos * width_) ||
			static_cast<int>(array_.size()) <= (x_pos + y_pos * width_)) {
			throw("�͈͊O�ɃA�N�Z�X");
		}
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
		if (0 > (x_pos + y_pos * width_) ||
			static_cast<int>(array_.size()) <= (x_pos + y_pos * width_)) {
			throw("�͈͊O�ɃA�N�Z�X");
		}
		return array_.at(x_pos + y_pos * width_);
	}

	const T& operator()(int pos)const {
		if (0 > pos ||
			static_cast<int>(array_.size()) <= pos) {
			throw("�͈͊O�ɃA�N�Z�X");
		}
		return array_.at(pos);
	}
	T& operator()(int pos){
		if (0 > pos ||
			static_cast<int>(array_.size()) <= pos) {
			throw("�͈͊O�ɃA�N�Z�X");
		}
		return array_.at(pos);
	}

private:
	std::vector<T> array_; ///<�X�e�[�W�f�[�^
	int width_; ///<����
	int height_; ///<�c��
};
#endif //INCLUDED_CELL_H