#include "parent.h"
#include "../../state.h"
#include <sstream>
#include "../../file_manager.h"
#include "../../game_lib.h"
//��K�w�O
#include "../parent.h"
//���K�w
#include "clear.h"
#include "loading.h"
#include "menu.h"
#include "play.h"
namespace sequence {
	namespace game{
		/**
		* �R���X�g���N�^
		*/
		Parent::Parent(int stage_id)
			:next_(kNone), stage_id_(stage_id), state_(nullptr),
			clear_(nullptr), loading_(nullptr),
			menu_(nullptr), play_(nullptr){

			loading_ = new Loading();
		}
		/**
		* �f�X�g���N�^
		*/
		Parent::~Parent() {
			SAFE_DELETE(clear_);
			SAFE_DELETE(loading_);
			SAFE_DELETE(menu_);
			SAFE_DELETE(play_);
			SAFE_DELETE(state_);
		}
		/**
		* �X�V
		*/
		void Parent::Update(GrandParent* parent) {
			switch (next_) {
			case kTitle:
				parent->MoveTo(GrandParent::kTitle);
				break;
			case kStageSelect:
				parent->MoveTo(GrandParent::kSelectStage);
				break;
			case kPlay:
				SAFE_DELETE(loading_);
				play_ = new Play();
				break;
			case kClear:
				SAFE_DELETE(play_)
				clear_ = new Clear();
				break;
			case kMenu:
				menu_ = new Menu();
				break;
			
			}
			next_ = kNone;

			if (clear_) {
				clear_->Update(this);
			}
			else if (loading_) {
				loading_->Update(this);
			}
			else if (menu_) {
				menu_->Update(this);
			}
			else if (play_) {
				play_->Update(this);
			}
			else if (clear_) {
				clear_->Update(this);
			}
		}
		/**
		* �V�[�P���X�J��
		* @details �ړ���̃V�[���������Ɏ��
		* @param [in] �ړ���
		*/
		void Parent::MoveTo(Seq next) {
			next_ = next;
		}
		/**
		* �q�ɔԂ̃N���X��new����
		*/
		void Parent::StartLoading() {
			///�ǂݍ��ރt�@�C��
			std::stringstream file_directory;
			file_directory << "map/map" << stage_id_ << ".txt";///<�t�@�C���ւ̃f�B���N�g��+�t�@�C����

			std::string file_data = FileManager::GetInstance()->ReadMapFile(file_directory.str());

			state_ = new State(file_data);
		}
		/**
		* �q�ɔԂւ̃|�C���^
		*/
		State* Parent::GetState() {
			return state_;
		}
	}
}