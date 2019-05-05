/**
* @file main.cpp
* @brief メインコード
* @author YouTE
* @date 2019/05/02
*/
#include <iostream>
#include "frame_work.h"
#include "sokoban.h"
int main() {

	FrameWork::Create();
	Sokoban sokoban;
	sokoban.Init();
	sokoban.Draw();
	while (!sokoban.Clear()) {
		sokoban.Update();
		sokoban.Draw();
	}
	FrameWork::Destory();
	return 0;
}