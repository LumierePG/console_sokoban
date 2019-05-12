/**
* @file stage.h
* @brief ステージを扱うクラス
* @author YouTE
* @date 2019/05/03
*/
#pragma once
#include "cell.h"
#include <string>

/**
* @class ステージを扱うクラス "src/stage.h"
* ステージ関連はここで扱う
*/
class State {
private:
	///<ステージデータ
	enum Object {
		kWall,			///<'#'壁
		kSpace,			///<' '空白
		kGoal,			///<'.'ゴール
		kMan,			///<'p'人
		kManOnGoal,		///<'P'ゴール上の人
		kBaggage,		///<'o'荷物
		kBaggageOnGoal,	///<'O'ゴール上の荷物

		kUnknown,		///<'?'それ以外のデータ
	};
public:
	State(const std::string& stage_data); ///<コンストラクタ
	State(const State& obj);///<コピーコンストラクタ
	State& operator=(const State& obj); ///<代入演算子
	~State(); ///<デストラクタ

	void Draw()const; ///<ステージの描画

	void Reset(); ///初期状態に戻す
	void SetSize(int* width, int* height);///横幅と縦幅の取得


	void Update(int difference_x, int difference_y);///更新
	void SearchMan(int* x_pos, int* y_pos); ///<人判定のデータの位置を探す
	bool CheckOutOfRange(int x_pos, int y_pos)const; ///<移動先が範囲外かチェックする
	int CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y)const;
	void MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y); ///<引数によって更新パターンを変える
	bool SearchObject(Object obj)const; ///<引数の探したいデータを検索する
	bool Clear()const;///<クリアしたかの判定

private:
	Cell<Object>* objects_; ///cellクラスで配列を管理する
	std::string stage_data_; ///ステージデータ

	void SetStageData(); ///<ステージデータを設定する

	void Draw_obj(Object obj) const; ///<引数に合わせたオブジェクトを描画する
};