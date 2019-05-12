/**
* @file main.cpp
* @brief メインコード
* @author YouTE
* @date 2019/05/02
*/
#include <iostream>
#include "game_lib.h"
#include "frame_work.h"
#include "seq/parent.h"
int main() {

	try{
		FrameWork::Create();

		sequence::Parent parent;
		while (1) {
			
			parent.Update();
		}
		FrameWork::Destory();
	}
	catch (const std::exception& ex) {
		ex.what();
	}
	
	return 0;
}