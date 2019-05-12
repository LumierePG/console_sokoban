/**
* @file parent.h
* シーケンス内の実装を記述"src/seq/game/parent.h"
* @details game内のシーケンスの親として、シーケンスを管理する実装を行う
* @author YouTE
* @date 2019/05/06
*/
#pragma once
class State;
namespace sequence {
	class Parent;
	namespace game {
		class Clear;
		class Loading;
		class Menu;
		class Play;
		
		class Parent {
			typedef sequence::Parent GrandParent; //一階層前のシーケンスをまとめたクラス
		public:
			///Gameシーケンス
			enum Seq {
				kTitle, //上階層
				kStageSelect, //上階層
				
				kClear,
				kMenu,
				kPlay,

				kNone,
			};
		public:
			Parent(int stage_id);
			~Parent();

			void Update(GrandParent* parent); ///<更新
			void MoveTo(Seq next); ///<シーケンス遷移
			void StartLoading(); ///<倉庫番の読み込みを始める
			
			State* GetState();
			
		private:
			State* state_; ///倉庫番へのポインタ
			Seq next_; ///<現在のシーン主にnew用なので最後にkNoneを入れる
			int stage_id_;///遊ぶステージデータの番号

			Clear* clear_;
			Loading* loading_; ///<ロードへのポインタ
			Menu* menu_;
			Play* play_;///<プレイへのポインタ
			
			
			
		};
	}
}
