/**
* @file parent.h
* シーケンス内の実装を記述"src/seq/parent.h"
* @details シーケンスの親として、シーケンスを管理する実装を行う
* @author YouTE
* @date 2019/05/06
*/
#pragma once
namespace sequence {
	class Title;
	class SelectStage;

	namespace game {
		class Parent;
	}
}
namespace sequence {
	class Parent {
	public:
		///Sequenceシーケンスを管理
		enum Seq{
			kTitle, 
			kSelectStage,
			kGame,//下階層

			kNone,
		};
	public:
		Parent(); ///<コンストラクタ
		~Parent(); ///<デストラクタ
	
		void Update(); ///<更新

		void MoveTo(Seq next);///<シーケンス遷移
		void SetStageId(int arg_stage_id); ///<遊ぶステージの番号
	private:
		Title* title_; ///<タイトルのポインタ
		SelectStage* select_stage_; ///セレクトステージのポインタ
		game::Parent* game_;///ゲームへのポインタ

		Seq next_;///<次に移行シーン 主にnew用なので最後にkNoneを入れる
		int stage_id_; ///ステージの番号
	};
}