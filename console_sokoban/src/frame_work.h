/**
* @file frame_work.h
* �}�l�[�W���[�N���X���܂Ƃ߂�������L�q"src/frame_work.h"
* @details �}�l�[�W���[�N���X���܂Ƃ߂����
* @author YouTE
* @date 2019/05/06
*/
#pragma once
class FrameWork {
public:
	static void Create();
	static void Destory();
private:
	static FrameWork* instance_;
	FrameWork();
	FrameWork(const FrameWork& obj) {};
	~FrameWork();
};