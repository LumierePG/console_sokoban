#include "title.h"
#include <iostream>
#include "parent.h"
#include "../key_manager.h"
namespace sequence {
	/**
	* 描画処理
	* @details タイトル画面の描画
	*/
	void Title::Draw() {
		std::cout << "\
##########\n\
#        #\n\
# 倉庫番 #\n\
#        #\n\
##########\n";
	}
	/**
	* 更新
	* @param [out] parent シーケンス移動用
	*/
	void Title::Update(Parent* parent) {

		Draw();

		//キー操作がステージ選択画面へシーンを移行する
		char ch = KeyManager::GetInstance()->GetKey();

		if (ch) {
			parent->MoveTo(sequence::Parent::kSelectStage);
		}
		
	}
}