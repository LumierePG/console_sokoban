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
class Stage {
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
	Stage(); ///<コンストラクタ
	Stage(const Stage& obj);///<コピーコンストラクタ
	Stage& operator=(const Stage& obj); ///<代入演算子
	~Stage(); ///<デストラクタ
	bool Init(const std::string& map_name); ///<初期化

	void Draw(); ///<ステージの描画

	bool SearchMan(int* x_pos, int* y_pos); ///<人判定のデータの位置を探す
	bool CheckOutOfRange(int x_pos, int y_pos); ///<移動先が範囲外かチェックする
	int CheckMovableMan(int expectation_man_x_pos, int expectation_man_y_pos, int difference_x, int difference_y);
	void MoveObject(int pattern, int man_x_pos, int man_y_pos, int difference_x, int difference_y); ///<引数によって更新パターンを変える
	bool SearchObject(Object obj); ///<引数の探したいデータを検索する
	bool Clear();///<クリアしたかの判定

	
private:
	Cell<Object>* stage_data_; ///<cellクラスで配列を管理する

	bool SetWidthHeight(const std::string& map_data, int* width, int* height); ///<横縦幅を取得する
	void SetStageData(const std::string& map_data, Cell<Object>* cell); ///<ステージデータを設定する

	void Draw_obj(Object obj); ///<引数に合わせたオブジェクトを描画する
};