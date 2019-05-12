#include "play.h"
#include "parent.h"
#include "../../state.h"
#include "../../key_manager.h"
namespace sequence {
	namespace game {
		/**
		* �X�V
		*/
		void Play::Update(Parent* parent) {
			State* state = parent->GetState();
			bool flag = false;

			flag = state->Clear();
			if (flag) {
				parent->MoveTo(Parent::kClear);
				return;
			}
			Draw(parent);

			//�L�[����
			char key = KeyManager::GetInstance()->GetKey();
			//x��y���̈ړ�����
			int difference_x, difference_y;
			difference_x = difference_y = 0;
			
			flag = MovablePushKey(key, &difference_x, &difference_y);
			if (!flag) {
				return;///�֐��𔲂���
			}
			//�X�V
			state->Update(difference_x, difference_y);

			
		}
		/**
		* �`��
		*/
		void Play::Draw(Parent* parent) {
			State* state = parent->GetState();
			state->Draw();
		}
		/**
		* �ړ��\�ȏꏊ�ւ̃L�[�������ꂽ��
		* @param [in] key �L�[����
		* @param [out] *x_pos x���̈ړ�����
		* @param [out] *y_pos y���̈ړ�����
		*/
		bool Play::MovablePushKey(char key, int* x_pos, int* y_pos) {
			int difference_x, difference_y;
				difference_x = difference_y = 0;
				switch (key) {
				case 'a':case 'A': --difference_x; break;
				case 'd':case 'D': ++difference_x; break;
				case 'w':case 'W': --difference_y; break;
				case 's':case 'S': ++difference_y; break;
				}
			
				if (difference_x != 0 || difference_y != 0) {
					*x_pos = difference_x;
					*y_pos = difference_y;
					return true;
				}
				return false;
		}
	}
}