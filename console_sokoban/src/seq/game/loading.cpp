#include "loading.h"
#include <iostream>
#include "parent.h"
namespace sequence {
	namespace game {
		/**
		* コンストラクタ
		*/
		Loading::Loading() 
			:counter_(0), start_load_flag_(false) {
		
		}
		/**
		* デストラクタ
		*/
		Loading::~Loading() {
		
		}
		/**
		* 更新
		* @details sokobanを読み込む　カウントをして一定時間経つとゲーム画面へ移行
		* @param [out] *parent 次のシーンに移動用
		*/
		void Loading::Update(Parent* parent) {
			Draw();
			if (!start_load_flag_) {		
				parent->StartLoading();
				start_load_flag_ = true;
			}
			++counter_;
			if (counter_ % 60 == 0) {
				parent->MoveTo(Parent::kPlay);
			}
		}
		/**
		* 描画
		*/
		void Loading::Draw() {
			std::system("cls");
			std::cout << "ろ～ど中" << std::endl;
		}
	}
}