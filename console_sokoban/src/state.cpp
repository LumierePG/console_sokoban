#include "state.h"
#include "game_lib.h" ///
#include "file_manager.h"
#include <sstream>
#include <algorithm>
#include <iostream>

/**
* コンストラクタ
* @param [in] map_name マップ名
*/
State::State(const std::string& stage_data)
	:objects_(nullptr){

	stage_data_ = stage_data;
	//データ終端に改行とNULL終端の追加
	//stage_data_.append("\n\0");
	//Resetで横縦幅はわかるのでデフォ呼び
	objects_ = new Cell<Object>();
	//読み込んだデータから初期処理をする
	Reset();

}
/**
* コピーコンストラクタ
*/
State::State(const State& obj) {

	int width = obj.objects_->GetWidth();
	int height = obj.objects_->GetHeight();
	objects_ = new Cell<Object>(width, height);

	objects_->SetSize(width, height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Object o = obj.objects_->operator()(x, y);
			(*objects_)(x,y) = o;
		}
	}
}
/**
* 代入演算子
*/
State& State::operator=(const State& obj) {
	//自己代入禁止
	if (this != &obj) {
		SAFE_DELETE(objects_);
		int width = obj.objects_->GetWidth();
		int height = obj.objects_->GetHeight();
		objects_ = new Cell<Object>(width,height);
		
		objects_->SetSize(width, height);

		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				Object o = obj.objects_->operator()(x, y);
				(*objects_)(x, y) = o;
			}
		}
	}
	return *this;
}
/**
* デストラクタ
*/
State::~State() {
	SAFE_DELETE(objects_);
}
/**
* 初期状態に戻す
* 
*/
void State::Reset() {
	//横幅と縦幅を読み込んだファイルデータからセット
	int width, height;
	SetSize(&width,&height);
	//ステージのサイズと縦横幅のセット
	objects_->SetSize(width, height);
	//ステージをセット
	SetStageData();
}
/**
* 横幅と縦幅をマップデータから取得
* @param [in] map_data マップデータ
* @param [out] *width 横幅
* @param [out] *height 縦幅
*/
void State::SetSize(int* width, int* height) {
	int x, y;
	int max_width, max_height;
	x = y = max_width = max_height = 0;

	for (auto t : stage_data_) {
		switch (t) {
		case '#':case ' ':case '.':
		case 'p':case 'P':case 'o':case 'O':
			++x;
			break;
		case '\n':
			++y;
			//最大値更新
			max_width = std::max(x, max_width);
			max_height = std::max(y, max_height);
			x = 0;
			break;
		}
	}
	if (max_width == 0 || max_height == 0) {
		throw("マップデータが壊れてます。");
	}
	else {
		*width = max_width;
		*height = max_height;
	}
}
/**
* ステージデータを設定
* @param [in] map_data このデータを元にステージデータを作成
* @param [out] stage_data 新規作成するステージデータ
*/
void State::SetStageData() {

	int index = 0;
	Object obj;

	for (auto t : stage_data_) {
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
			(*objects_)(index) = obj;
			++index;
		}	
	}
}
/**
* 描画
*/
void State::Draw() const {
	std::system("cls");
	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Draw_obj((*objects_)(x,y));
		}
		std::cout << std::endl;
	}
}
/**
* 引数に合わせたオブジェクトを描画する
* @detail Draw()で使用する
* @param [in] index オブジェクトをindex代わりにして表示
*/
void State::Draw_obj(Object index) const {
	char data[] = {'#', ' ', '.', 'p', 'P', 'o', 'O'};
	std::cout << data[index];
}
/**
* 人判定のデータを探す
* @param [out] *x_pos x軸位置
* @param [out] *y_pos y軸位置
*/
void State::SearchMan(int* x_pos, int* y_pos) {

	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*objects_)(x, y) == kMan ||
				(*objects_)(x, y) == kManOnGoal) {
				*x_pos = x;
				*y_pos = y;
				return;
			}
		}
	}
	throw("主人公が見当たらない。あり得ない");
}
/**
* 移動先が範囲外かチェックする
* @param [in] x_pos x軸の人の位置
* @param [in] y_pos y軸の人の位置
* @retval true 範囲内
* @retval false 範囲外
*/
bool State::CheckOutOfRange(int x_pos, int y_pos) const{
	
	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
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
int State::CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y) const{
	
	//移動先が移動可能かチェック
	if ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggage ||
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) {
		///更に予想の位置
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		//再度マップ内の判定
		bool flag = CheckOutOfRange(next_exprection_man_x_pos, next_exprection_man_y_pos);
		if (!flag) {
			return -1;
		}
		//更に先の移動先が移動可能かチェック
		if ((*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal ||
			(*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kSpace) {
			return 1;
		}
	}
	else if ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal ||
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kSpace) {
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
void State::MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y) {
	int expectation_man_x_pos = man_x_pos + difference_x;
	int expectation_man_y_pos = man_y_pos + difference_y;
	switch (pattern) {
	case 0: ///移動先がゴール又はスペースだった場合
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) = ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kGoal) ? kManOnGoal : kMan;
		(*objects_)(man_x_pos, man_y_pos) = ((*objects_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
		break;
	case 1: ///<移動先が荷物で更に先がゴール又はスペースだった場合
		int next_exprection_man_x_pos = expectation_man_x_pos + difference_x;
		int next_exprection_man_y_pos = expectation_man_y_pos + difference_y;
		(*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) = ((*objects_)(next_exprection_man_x_pos, next_exprection_man_y_pos) == kGoal) ? kBaggageOnGoal : kBaggage;
		(*objects_)(expectation_man_x_pos, expectation_man_y_pos) = ((*objects_)(expectation_man_x_pos, expectation_man_y_pos) == kBaggageOnGoal) ? kManOnGoal : kMan;
		(*objects_)(man_x_pos, man_y_pos) = ((*objects_)(man_x_pos, man_y_pos) == kManOnGoal) ? kGoal : kSpace;
	}
}
/**
* 引数の探したいデータを検索する
* @param [in] 探したいステージデータ
* @retval true データを発見
* @retval false データを未発見
*/
bool State::SearchObject(Object obj) const{
	int width = objects_->GetWidth();
	int height = objects_->GetHeight();
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if ((*objects_)(x, y) == obj) {
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
bool State::Clear() const{
	bool flag = SearchObject(kBaggage);
	///データを未発見の場合はクリア
	if (!flag) { 
		return true;
	}
	///データを発見の場合は未クリア
	return false;
}
/**
* 移動先をチェックして可能ならオブジェクトを更新
* @param [in] difference_x x差分
* @param [in] difference_y y差分
*/
void State::Update(int difference_x, int difference_y) {
	//人の現在位置
	int man_x_pos, man_y_pos;
	SearchMan(&man_x_pos, &man_y_pos);

	//移動先の予測の位置
	int expectation_man_x_pos = man_x_pos + difference_x;
	int expectation_man_y_pos = man_y_pos + difference_y;
	bool flag = CheckOutOfRange(expectation_man_x_pos, expectation_man_y_pos);
	if (!flag) {
		return; ///<移動先が範囲外なら処理を抜ける
	}
	int move_pattern = CheckMovableMan(expectation_man_x_pos, expectation_man_y_pos, difference_x, difference_y);
	if (move_pattern == -1) {
		return; ///<移動先が移動不可なら処理を抜ける
	}
	MoveObject(move_pattern, man_x_pos, man_y_pos, difference_x, difference_y);
}