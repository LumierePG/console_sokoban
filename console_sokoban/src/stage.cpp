#include "stage.h"
#include "file_manager.h"
#include <sstream>
#include <algorithm>
#include <iostream>
/**
* コンストラクタ
*/
Stage::Stage() 
	:stage_data_(nullptr){

}
/**
* コピーコンストラクタ
*/
Stage::Stage(const Stage& obj) {

	int width = obj.stage_data_->GetWidth();
	int height = obj.stage_data_->GetHeight();
	stage_data_ = new Cell<Object>(width, height);

	stage_data_->SetWidth(width);
	stage_data_->SetHeight(height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object o = obj.stage_data_->operator()(x, y);
			stage_data_->Add(x, y, o);
		}
	}
}
/**
* 代入演算子
*/
Stage& Stage::operator=(const Stage& obj) {
	//自己代入禁止
	if (this != &obj) {
		delete stage_data_;
		stage_data_ = nullptr;


		int width = obj.stage_data_->GetWidth();
		int height = obj.stage_data_->GetHeight();
		stage_data_ = new Cell<Object>(width,height);
		
		stage_data_->SetWidth(width);
		stage_data_->SetHeight(height);

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Object o = obj.stage_data_->operator()(x,y);
				stage_data_->Add(x, y, o);
			}
		}
	}
	return *this;
}
/**
* デストラクタ
*/
Stage::~Stage() {
	delete stage_data_;
	stage_data_ = nullptr;
}
/**
* 読み込んだファイルからcellデータを扱う
* @param [in] map_name マップ名
* @retval true ステージデータの作成成功
* @retval false 初期化の時点で失敗
*/
bool Stage::Init(const std::string& map_name) {

	std::stringstream file_name;
	file_name << "map/";
	file_name << map_name;
	std::ifstream* fin;
	fin = FileManager::GetInstance()->ReadFile(file_name.str());

	std::stringstream stio;
	std::string ss;

	while (getline(*fin,ss)) {
		stio << ss;
		///行の終わりにわかりやすく改行コードを追加
		stio << '\n';
		ss.erase();
	}
	std::string map_data = stio.str();
	int width, height;

	bool flag;
	flag = SetWidthHeight(map_data, &width, &height);
	///横幅と縦幅が取得出来なかったら初期化失敗扱い
	if (!flag) {
		return false;
	}
	stage_data_ = new Cell<Object>(width, height);
	SetStageData(map_data, stage_data_);
	
	return true;
}
/**
* 横縦の取得
* @param [in] stage_data ファイルから読み込んだデータ
* @param [out] *width 横幅
* @param [out] *height 縦幅
* @retval true 取得成功
* @retval false 取得失敗
*/
bool Stage::SetWidthHeight(const std::string& map_data, int* width, int* height) {
	int x, y;
	int max_width, max_height;
	x = y = max_width = max_height = 0;
	
	for (auto t : map_data) {
		switch (t) {
		case '#':case ' ':case '.':
		case 'p':case 'P':case 'o':case 'O':
			++x;
			break;
		case '\n':
			++y;
			max_width	= std::max(x, max_width);
			max_height = std::max(y, max_height);
			x = 0;
			break;
		}
	}
	if (max_width != 0 || max_height != 0) {
		*width = max_width;
		*height = max_height;
		return true;
	}
	return false;
}
/**
* ステージデータを設定
* @param [in] map_data このデータを元にステージデータを作成
* @param [out] stage_data 新規作成するステージデータ
*/
void Stage::SetStageData(const std::string& map_data, Cell<Object>* stage_data) {

	int index = 0;
	Object obj;

	for (auto t : map_data) {
		switch (t) {
		case '#': obj = kWall; break;
		case ' ': obj = kSpace; break;
		case '.': obj = kGoal; break;
		case 'p': obj = kMan; break;
		case 'P': obj = kManOnGoal; break;
		case 'o': obj = kBaggage; break;
		case 'O': obj = kBaggageOnGoal; break;

		default: obj = kUnknown; break;

		}
		if (obj != kUnknown) {
			stage_data->Add(index, obj);
			++index;
		}	
	}
}
/**
* 描画
*/
void Stage::Draw() {
	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Draw_obj((*stage_data_)(x,y));
		}
		std::cout << std::endl;
	}
}
/**
* 引数に合わせたオブジェクトを描画する
* @detail Draw()で使用する
* @param [in] index オブジェクトをindex代わりにして表示
*/
void Stage::Draw_obj(Object index) {
	char data[] = {'#', ' ', '.', 'p', 'P', 'o', 'O'};
	std::cout << data[index];
}
/**
* 人判定のデータを探す
* @param [out] *x_pos x軸位置
* @param [out] *y_pos y軸位置
* @retval true 見つかった
* @retval false　見つからない
*/
bool Stage::SearchMan(int* x_pos, int* y_pos) {

	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*stage_data_)(x, y) == kMan ||
				(*stage_data_)(x, y) == kManOnGoal) {
				*x_pos = x;
				*y_pos = y;
				return true;
			}
		}
	}
	return false;
}
/**
* 移動先が範囲外かチェックする
* @param [in] x_pos x軸の人の位置
* @param [in] y_pos y軸の人の位置
* @retval true 範囲内
* @retval false 範囲外
*/
bool Stage::CheckOutOfRange(int x_pos, int y_pos) {
	
	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	///マップ外に位置してないか判定
	if (0 <= x_pos &&
		x_pos < width &&
		0 < y_pos &&
		y_pos < height) {
		return true;
	}
	return false;
}
/**
* 移動先が移動可能かのチェックする
* @details 移動先が移動可能かのチェックして荷物があった場合は更にその先も移動可能かチェックする
* @param [in] expectation_man_x_pos x軸の移動の予想先
* @param [in] expectation_man_y_pos y軸の移動の予想先
* @param [in] difference_x x軸の移動差分　移動先が移動可能な場合先も調べる為必要
* @param [in] difference_y y軸の移動差分
* @retval 0 移動可能 パターン1 移動先がすぐ移動可能な場合
* @retval 1 移動可能 パターン2 移動先に荷物が存在するがその先も移動可能な場合
* @retval -1 移動不可
*/
int Stage::CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y) {
	
	//移動先が移動可能かチェック
	if ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggage ||
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) {
		///更に予想の位置
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		//再度マップ内の判定
		bool flag = CheckOutOfRange(next_exprection_man_x_pos, next_exprection_man_y_pos);
		if (!flag) {
			return -1;
		}
		//更に先の移動先が移動可能かチェック
		if ((*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal ||
			(*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kSpace) {
			return 1;
		}
	}
	else if ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal || 
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kSpace) {
		return 0;
	}
	return -1;
}
/**
* ステージ上のオブジェクトに更新をかける
* @details 
* @param [in] pattern 更新の種類
* @param [in] man_x_pos x軸の人の位置
* @param [in] max_y_pos y軸の人の位置
* @param [in] difference_x x軸の移動差分
* @param [in] difference_y y軸の移動差分
*/
void Stage::MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y) {
	int expectation_man_x_pos = man_x_pos + difference_x;
	int expectation_man_y_pos = man_y_pos + difference_y;
	switch (pattern) {
	case 0: ///移動先がゴール又はスペースだった場合
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) = ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal) ? kManOnGoal : kMan;
		(*stage_data_)(man_x_pos, man_y_pos) = ((*stage_data_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
		break;
	case 1: ///<移動先が荷物で更に先がゴール又はスペースだった場合
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		(*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) = ((*stage_data_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal) ? kBaggageOnGoal : kBaggage;
		(*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) = ((*stage_data_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) ? kManOnGoal : kMan;
		(*stage_data_)(man_x_pos, man_y_pos) = ((*stage_data_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
	}
}
/**
* 引数の探したいデータを検索する
* @param [in] 探したいステージデータ
* @retval true データを発見
* @retval false データを未発見
*/
bool Stage::SearchObject(Object obj) {
	int width = stage_data_->GetWidth();
	int height = stage_data_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*stage_data_)(x, y) == obj) {
				return true;
			}
		}
	}
	return false;
}
/**
* クリアしたかの判定
* @retval クリアした
* @retval 未クリア
*/
bool Stage::Clear() {
	bool flag = SearchObject(kBaggage);
	///データを未発見の場合はクリア
	if (!flag) { 
		return true;
	}
	///データを発見の場合は未クリア
	return false;
}