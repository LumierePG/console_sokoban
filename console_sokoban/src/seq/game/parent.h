/**
* @file parent.h
* �V�[�P���X���̎������L�q"src/seq/game/parent.h"
* @details game���̃V�[�P���X�̐e�Ƃ��āA�V�[�P���X���Ǘ�����������s��
* @author YouTE
* @date 2019/05/06
*/
#pragma once
class State;
namespace sequence {
	class Parent;
	namespace game {
		class Clear;
		class Loading;
		class Menu;
		class Play;
		
		class Parent {
			typedef sequence::Parent GrandParent; //��K�w�O�̃V�[�P���X���܂Ƃ߂��N���X
		public:
			///Game�V�[�P���X
			enum Seq {
				kTitle, //��K�w
				kStageSelect, //��K�w
				
				kClear,
				kMenu,
				kPlay,

				kNone,
			};
		public:
			Parent(int stage_id);
			~Parent();

			void Update(GrandParent* parent); ///<�X�V
			void MoveTo(Seq next); ///<�V�[�P���X�J��
			void StartLoading(); ///<�q�ɔԂ̓ǂݍ��݂��n�߂�
			
			State* GetState();
			
		private:
			State* state_; ///�q�ɔԂւ̃|�C���^
			Seq next_; ///<���݂̃V�[�����new�p�Ȃ̂ōŌ��kNone������
			int stage_id_;///�V�ԃX�e�[�W�f�[�^�̔ԍ�

			Clear* clear_;
			Loading* loading_; ///<���[�h�ւ̃|�C���^
			Menu* menu_;
			Play* play_;///<�v���C�ւ̃|�C���^
			
			
			
		};
	}
}
