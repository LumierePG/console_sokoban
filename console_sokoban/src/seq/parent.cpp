#include "parent.h"
#include "title.h"
#include "select_stage.h"
#include "game/parent.h"
#include "../game_lib.h"
namespace sequence {
	/**
	* �R���X�g���N�^
	* @details �ŏ��̃V�[���̓^�C�g��
	*/
	Parent::Parent()
		: title_(nullptr), select_stage_(nullptr), game_(nullptr),
		next_(kTitle) {
		
	}
	/**
	* �f�X�g���N�^
	*/
	Parent::~Parent() {
		SAFE_DELETE(title_);
		SAFE_DELETE(select_stage_);	
		SAFE_DELETE(game_);
	}
	/**
	* �X�V
	*/
	void Parent::Update() {
		///���߂ČĂяo���ꂽ���ɏ�������p
		switch (next_) {
			///���V�[���̓^�C�g���Ȃ̂�
		case kTitle:
			SAFE_DELETE(select_stage_);
			SAFE_DELETE(game_);
			///�^�C�g���ւ̃|�C���^��new����
			title_ = new Title();
			break;
		case kSelectStage:
			SAFE_DELETE(title_);
			SAFE_DELETE(game_);
			select_stage_ = new SelectStage();
			break;
		case kGame:
			SAFE_DELETE(title_);
			SAFE_DELETE(select_stage_);
			game_ = new game::Parent(stage_id_);
			break;
		}
		///�V�[�P���X�̈ړ���h����state_�ɃV�[�P���X�̈ړ�������kNone������
		next_ = kNone;

		///��state_�ɂ���ē���
		if (title_) {
			title_->Update(this);
		}
		else if (select_stage_) {
			select_stage_->Update(this);
		}
		else if (game_) {
			game_->Update(this);
		}
		
	}
	/**
	* �V�[�P���X�J��
	* @param[in] next�@�V�[���̈ړ���
	*/
	void Parent::MoveTo(Seq next) {
		next_ = next;
	}
	/**
	* �V�ԃX�e�[�W�̔ԍ����Z�b�g����
	* @param [in] arg_stage_id
	*/
	void Parent::SetStageId(int arg_stage_id) {
		stage_id_ = arg_stage_id;
	}
}