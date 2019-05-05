/**
* @file sokoban.h
* ゲームの中身の実装の記述"src/sokoban.h"
* @details ゲーム自体の実装を行う　
* @author YouTE
* @date 2019/05/04
*/
#pragma once
#include <vector>
class Stage;
class Sokoban {
public:
	Sokoban(); ///<コンストラクタ
	~Sokoban(); ///<デストラクタ
	void Init(); ///<初期化処理
	void Init(int stage_number);///<初期化の処理 ステージ選択
	
	bool Update(); ///<更新
	void Draw(); ///<描画
	bool Clear(); ///<クリアしたかどうかの判定
	
private:
	Stage* stage_; ///<使用するステージデータ
	Stage* stage_list_; ///読み込んだステージデータ群置き場
	std::vector<std::string> map_name_list; ///<ステージ選択の時にmapを選べるようにする

	bool MovablePushKey(char key, int* x_pos, int* y_pos); ///<移動したか判定
	void SelectStage(int select_stage); ///ステージを変更する
};

//vectorにオブジェクトを持たせてはいけない