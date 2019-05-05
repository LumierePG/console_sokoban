#include "frame_work.h"
#include "key_manager.h"
#include "file_manager.h"
///唯一のインスタンス
FrameWork* FrameWork::instance_ = nullptr;
/**
* コンストラクタ
* @details マネージャークラスのインスタンス生成
*/
FrameWork::FrameWork() {
	FileManager::Create();
	KeyManager::Create();
}
/**
* デストラクタ
* @details マネージャークラスのインスタンス破棄
*/
FrameWork::~FrameWork() {
	FileManager::Destory();
	KeyManager::Destory();
}
/**
* 処理の始まりに呼ぶ
*/
void FrameWork::Create() {
	if (!instance_) {
		instance_ = new FrameWork;
	}
}
/**
* 処理の終わりに呼ぶ
*/
void FrameWork::Destory() {
	delete instance_;
	instance_ = nullptr;
}