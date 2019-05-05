/**
* @file cell.h
* セルクラスの記述 "src/cell.h"
* @details Stageクラスにcellクラスを一つ持たせてステージデータとして使う
* 引数付きのコンストラクタ呼び出し以外今の所機能しない。
* @author YouTE
* @date 2019/05/03
*/
#pragma once
#include <vector>
template <typename T>class Cell{
public:
	/**
	* デフォルトコンストラクタ
	* @details データメンバのwidth_,height_を0初期化しておく。<br>
	* 但しこの初期化をした場合はデータメンバ自体が0初期化しかされてないので、何処かでwidth_とheight_とarray_を代入しなければならない
 	*/
	Cell()
		: width_(0), height_(0){
		array_.resize(width_ * height_);
	}
	/**
	* 引数付きコンストラクタ
	* @param [in] arg_width データメンバのwidth_の初期化
	* @param [in] arg_height データメンバのheight_の初期化
	*/
	Cell(int arg_width, int arg_height) 
		: width_(arg_width), height_(arg_height){
		array_.resize(width_ * height_);
	}
	/**
	* array_を引数のx_pos,y_posの位置を使って更新する
	* @param [in] x_pos 横の位置
	* @param [in] y_pos 縦の位置
	* @param [in] data 更新するデータ
	* @retval true 有効なインデックスを指定
	* @retval false 無効なインデックスを指定
	*/
	bool Add(int x_pos, int y_pos, T data) {
		if (0 <= (x_pos + y_pos * width_) &&
			(x_pos + y_pos * width_) < static_cast<int>(array_.size())) {
			array_.at(x_pos + y_pos * width_) = data;
			return true;
		}
		return false;
	}
	/**
	* array_を引数のposの位置を使って更新する
	* @param [in] pos 更新したいインデックス
	* @param [in] data 更新するデータ
	* @retval true 有効なインデックスを指定
	* @retval false 無効なインデックスを指定
	*/
	bool Add(int pos, T data) {
		if (0 <= (pos) &&
			pos < static_cast<int>(array_.size())) {
			array_.at(pos) = data;
			return true;
		}
		return false;
	}
	/**
	* 横幅の取得
	* @return width_ 横幅
	*/
	int GetWidth() {
		return width_;
	}
	/**
	* 縦幅の取得
	* @return height_ 縦幅
	*/
	int GetHeight() {
		return height_;
	}
	/**
	* 横幅の設定
	* @param [in] arg_width メンバのwidth_を更新
	*/
	void SetWidth(int arg_width) {
		width_ = arg_width;
	}
	/**
	* 縦幅の設定
	* @param [in] arg_height メンバのheight_を更新
	*/
	void SetHeight(int arg_height) {
		height_ = arg_height;
	}
	/**
	* データのメンバのリサイズ
	* @param [in] size リサイズの大きさ
	*/
	void ArrayReSize(int size){
		array_.resize(size);
	}
	/**
	* 扱いやすいように演算子のオーバーロードを作成
	* @details 範囲外を指す事ができる為使い方に注意
	* TODO:expectionを今後追加予定
	* @param [in] x_pos 横の位置
	* @param [in] y_pos 縦の位置
	* @return 変更不可能なデータを返す
	*/
	const T& operator()(int x_pos, int y_pos) const{
		return array_.at(x_pos + y_pos * width_);
	}
	/**
	* 扱いやすいように演算子のオーバーロードを作成
	* @details 範囲外を指す事ができる為使い方に注意
	* @param [in] x_pos 横の位置
	* @param [in] y_pos 縦の位置
	* @return 変更可能なデータを返す
	*/
	T& operator()(int x_pos, int y_pos) {
		return array_.at(x_pos + y_pos * width_);
	}

private:
	std::vector<T> array_; ///<ステージデータ
	int width_; ///<横幅
	int height_; ///<縦幅
};