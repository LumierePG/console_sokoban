#include "select_stage.h"
#include "parent.h"
#include <iostream>
#include "../key_manager.h"
#include "../file_manager.h"
#include <fstream>
#include <string>
#include "../game_lib.h"
namespace sequence {
	/**
	* コンストラクタ
	* @details 外部ファイルからステージの数を読み込む
	*/
	SelectStage::SelectStage()
	:arrow_pos_(0), stage_num_(0){
		
		std::string file_data = FileManager::GetInstance()->ReadFile("map/maplist.txt");

		int start_pos = file_data.find("@map_num") + sizeof("@map_num") -1;
		int end_pos = file_data.find("@map_num_end");
		
		std::string temp = file_data.substr(start_pos, end_pos - start_pos);
		stage_num_ = std::atoi(temp.c_str());

		if (stage_num_ < 0) {
			throw("ステージの数が設定されていません");
		}
	}
	/**
	* デストラクタ
	*/
	SelectStage::~SelectStage(){

	}
	/**
	* 描画処理
	*/
	void SelectStage::Draw() {
		//コンソール画面をクリアする
		std::system("cls");
		//文言
		std::cout << "遊びたいステージを選んでね" << std::endl;

		for (int i = 0; i < stage_num_; ++i) {
			if (arrow_pos_ == i) {
				std::cout << "→";
			}
			std::cout << "ステージ" << i + 1 << std::endl;
		}
	}
	/**
	* 更新
	* @param [out] *parent シーン移動に使う
	* TODO:ステージを選択性にする。選択後Gameクラスへ選択したステージ番号を渡すようにする
	*/
	void SelectStage::Update(Parent* parent) {

		Draw();

		char ch = KeyManager::GetInstance()->GetKey();

		switch (ch) {
		case 'w':case 'W': --arrow_pos_; break;
		case 's':case 'S': ++arrow_pos_; break;
		case 'y':case 'Y':
			parent->SetStageId(arrow_pos_ +1);
			parent->MoveTo(sequence::Parent::kGame); 
			break;
		}
		if (0 > arrow_pos_) {
			arrow_pos_ = stage_num_ -1;
		}
		else if (arrow_pos_ >= stage_num_) {
			arrow_pos_ = 0;
		}
	}
}