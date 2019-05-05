#include "frame_work.h"
#include "key_manager.h"
#include "file_manager.h"
///�B��̃C���X�^���X
FrameWork* FrameWork::instance_ = nullptr;
/**
* �R���X�g���N�^
* @details �}�l�[�W���[�N���X�̃C���X�^���X����
*/
FrameWork::FrameWork() {
	FileManager::Create();
	KeyManager::Create();
}
/**
* �f�X�g���N�^
* @details �}�l�[�W���[�N���X�̃C���X�^���X�j��
*/
FrameWork::~FrameWork() {
	FileManager::Destory();
	KeyManager::Destory();
}
/**
* �����̎n�܂�ɌĂ�
*/
void FrameWork::Create() {
	if (!instance_) {
		instance_ = new FrameWork;
	}
}
/**
* �����̏I���ɌĂ�
*/
void FrameWork::Destory() {
	delete instance_;
	instance_ = nullptr;
}