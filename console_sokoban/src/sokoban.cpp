//#include "sokoban.h"
//#include <vector>
//#include <fstream>
//
//#include "file_manager.h"
//#include "key_manager.h"
//
//#include "state.h"
///**
//* コンストラクタ
//*/
//Sokoban::Sokoban() {
//	stage_ = new State();
//}
///**
//* デストラクタ
//*/
//Sokoban::~Sokoban() {
//	delete stage_;
//	stage_ = nullptr;
//	//TODO:配列の解放の後処理がわからん
//	delete[] stage_list_;
//	stage_list_ = nullptr;
//}
//
///**
//* 初期化処理
//*/
//void Sokoban::Init() {
//	//マップデータ名がすべて乗ってるファイルを読み込む
//	std::ifstream* fin;
//	fin = FileManager::GetInstance()->ReadFile("map/maplist.txt");
//
//	std::string ss;
//	///読み込みを管理するフラグ
//	bool flag = false;
//	while (std::getline(*fin, ss)) {
//
//		///マップの数を知りたいのでそこまで空読み
//		if (ss.compare("@map_name") == 0) {
//			flag = true;
//			getline(*fin, ss); ///<次の行に移行
//		}
//		///マップの数の読み込み集終了処理
//		else if (ss.compare("@map_name_end") == 0) {
//			flag = false;
//			break;
//		}
//		//マップ数の読み込み
//		if (flag) {
//			map_name_list.push_back(ss);
//			ss.erase(); ///<空にする
//		}	
//	}
//	FileManager::GetInstance()->CloseFile(fin);
//
//	//ステージの数が0以外なら
//	int stage_num = static_cast<int>(map_name_list.size());
//
//	if (0 < stage_num) {
//		stage_list_ = new Stage[stage_num];
//
//		for (int index = 0; index < stage_num; ++index) {
//			stage_list_[index].Init(map_name_list.at(index));
//		}
//	}
//	//ステージ選択がされない場合は最初のステージから
//	SelectStage(0);
//}
///**
//* 初期化処理
//* @details ファイル読み込みも兼ねた初期化処理
//* @param [in] select_stage 開始するステージ
//*/
//void Sokoban::Init(int select_stage) {
//	//マップデータ名がすべて乗ってるファイルを読み込む
//	std::ifstream* fin;
//	fin = FileManager::GetInstance()->ReadFile("map/maplist.txt");
//
//	std::string ss;
//	///読み込みを管理するフラグ
//	bool flag = false;
//	while (std::getline(*fin, ss)) {
//
//		///マップの数を知りたいのでそこまで空読み
//		if (ss.compare("@map_name") == 0) {
//			flag = true;
//			getline(*fin, ss); ///<次の行に移行
//		}
//		///マップの数の読み込み集終了処理
//		else if (ss.compare("@map_name_end") == 0) {
//			flag = false;
//			break;
//		}
//		//マップ数の読み込み
//		if (flag) {
//			map_name_list.push_back(ss);
//			ss.erase(); ///<空にする
//		}
//	}
//	FileManager::GetInstance()->CloseFile(fin);
//
//	//ステージの数が0以外なら
//	int stage_num = static_cast<int>(map_name_list.size());
//
//	if (0 < stage_num) {
//		stage_list_ = new Stage[stage_num];
//
//		for (int index = 0; index < stage_num; ++index) {
//			stage_list_[index].Init(map_name_list.at(index));
//		}
//	}
//	//実装範囲のステージを選択
//	if (select_stage <= stage_num) {
//		SelectStage(select_stage);
//	}
//}
///**
//* 描画
//*/
//void Sokoban::Draw() {
//	//コンソール画面をクリアする
//	std::system("cls");
//	stage_->Draw();
//}
///**
//* ステージを変更する処理
//* @param [in] stage_number　変更するステージ番号
//*/
//void Sokoban::SelectStage(int stage_number) {
//	*stage_ = stage_list_[stage_number];
//}
///**
//* ステージ内の行動を更新する　ゲーム実装部分
//*/
//bool Sokoban::Update() {
//	//キー入力
//	char key = KeyManager::GetInstance()->GetKey();
//	//x軸y軸の移動差分
//	int difference_x, difference_y;
//	difference_x = difference_y = 0;
//	
//	bool flag = MovablePushKey(key, &difference_x, &difference_y);
//	if (!flag) {
//		return false; ///<移動不可で処理を抜ける
//	}
//	//人の現在位置
//	int man_x_pos, man_y_pos;
//	flag = stage_->SearchMan(&man_x_pos, &man_y_pos);
//	if (!flag) {
//		return false; ///<人を発見できなかったので処理を抜ける
//	}
//	//移動先の予測の位置
//	int expectation_man_x_pos = man_x_pos + difference_x;
//	int expectation_man_y_pos = man_y_pos + difference_y;
//	flag = stage_->CheckOutOfRange(expectation_man_x_pos, expectation_man_y_pos);
//	if (!flag) {
//		return false; ///<移動先が範囲外なら処理を抜ける
//	}
//	int move_pattern = stage_->CheckMovableMan(expectation_man_x_pos, expectation_man_y_pos,difference_x, difference_y);
//	if (move_pattern == -1) {
//		return false; ///<移動先が移動不可なら処理を抜ける
//	}
//	stage_->MoveObject(move_pattern,man_x_pos, man_y_pos,difference_x, difference_y);
//
//	return true; ///更新成功
//}
///**
//* 移動可能な場所へのキーが押されたか
//* @param [in] key キー入力
//* @param [out] *x_pos x軸の移動差分
//* @param [out] *y_pos y軸の移動差分
//*/
//bool Sokoban::MovablePushKey(char key, int* x_pos, int* y_pos) {
//	int difference_x, difference_y;
//	difference_x = difference_y = 0;
//	switch (key) {
//	case 'a':case 'A': --difference_x; break;
//	case 'd':case 'D': ++difference_x; break;
//	case 'w':case 'W': --difference_y; break;
//	case 's':case 'S': ++difference_y; break;
//	}
//
//	if (difference_x != 0 || difference_y != 0) {
//		*x_pos = difference_x;
//		*y_pos = difference_y;
//		return true;
//	}
//	return false;
//}
///**
//* クリアしたかどうかの判定
//* @retval true　クリア
//* @retval false 未クリア
//*/
//bool Sokoban::Clear() {
//	return stage_->Clear();
//}