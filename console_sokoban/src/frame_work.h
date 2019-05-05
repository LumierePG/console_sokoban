/**
* @file frame_work.h
* マネージャークラスをまとめる実装を記述"src/frame_work.h"
* @details マネージャークラスをまとめる実装
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