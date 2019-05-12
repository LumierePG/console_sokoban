/**
* @file select_stage.h
* ステージ選択の実装 src/seq/select_stage.h
* @details ステージ選択の実装を行う
* @author YouTE
* @date 2019/05/06
*/
#pragma once

namespace sequence {
	class Parent;
	class SelectStage {
	public:

		SelectStage();
		~SelectStage();

		void Draw(); ///<描画処理
		void Update(Parent* parent); ///<更新
	private:
		int arrow_pos_; ///矢印の現在地
		int stage_num_; ///<外部ファイルからステージの数を読み込む
	};
}
