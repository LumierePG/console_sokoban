/**
* @file select_stage.h
* �X�e�[�W�I���̎��� src/seq/select_stage.h
* @details �X�e�[�W�I���̎������s��
* @author YouTE
* @date 2019/05/06
*/
#pragma once

namespace sequence {
	class Parent;
	class SelectStage {
	public:

		SelectStage();
		~SelectStage();

		void Draw(); ///<�`�揈��
		void Update(Parent* parent); ///<�X�V
	private:
		int arrow_pos_; ///���̌��ݒn
		int stage_num_; ///<�O���t�@�C������X�e�[�W�̐���ǂݍ���
	};
}
