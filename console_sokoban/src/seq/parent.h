/**
* @file parent.h
* �V�[�P���X���̎������L�q"src/seq/parent.h"
* @details �V�[�P���X�̐e�Ƃ��āA�V�[�P���X���Ǘ�����������s��
* @author YouTE
* @date 2019/05/06
*/
#pragma once
namespace sequence {
	class Title;
	class SelectStage;

	namespace game {
		class Parent;
	}
}
namespace sequence {
	class Parent {
	public:
		///Sequence�V�[�P���X���Ǘ�
		enum Seq{
			kTitle, 
			kSelectStage,
			kGame,//���K�w

			kNone,
		};
	public:
		Parent(); ///<�R���X�g���N�^
		~Parent(); ///<�f�X�g���N�^
	
		void Update(); ///<�X�V

		void MoveTo(Seq next);///<�V�[�P���X�J��
		void SetStageId(int arg_stage_id); ///<�V�ԃX�e�[�W�̔ԍ�
	private:
		Title* title_; ///<�^�C�g���̃|�C���^
		SelectStage* select_stage_; ///�Z���N�g�X�e�[�W�̃|�C���^
		game::Parent* game_;///�Q�[���ւ̃|�C���^

		Seq next_;///<���Ɉڍs�V�[�� ���new�p�Ȃ̂ōŌ��kNone������
		int stage_id_; ///�X�e�[�W�̔ԍ�
	};
}