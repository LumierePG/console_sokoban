#include "parent.h"
#include "title.h"
#include "select_stage.h"
#include "game/parent.h"
#include "../game_lib.h"
namespace sequence {
	/**
	* コンストラクタ
	* @details 最初のシーンはタイトル
	*/
	Parent::Parent()
		: title_(nullptr), select_stage_(nullptr), game_(nullptr),
		next_(kTitle) {
		
	}
	/**
	* デストラクタ
	*/
	Parent::~Parent() {
		SAFE_DELETE(title_);
		SAFE_DELETE(select_stage_);	
		SAFE_DELETE(game_);
	}
	/**
	* 更新
	*/
	void Parent::Update() {
		///初めて呼び出された時に処理する用
		switch (next_) {
			///現シーンはタイトルなので
		case kTitle:
			SAFE_DELETE(select_stage_);
			SAFE_DELETE(game_);
			///タイトルへのポインタをnewして
			title_ = new Title();
			break;
		case kSelectStage:
			SAFE_DELETE(title_);
			SAFE_DELETE(game_);
			select_stage_ = new SelectStage();
			break;
		case kGame:
			SAFE_DELETE(title_);
			SAFE_DELETE(select_stage_);
			game_ = new game::Parent(stage_id_);
			break;
		}
		///シーケンスの移動を防ぐ為state_にシーケンスの移動が無いkNoneを入れる
		next_ = kNone;

		///現state_によって動作
		if (title_) {
			title_->Update(this);
		}
		else if (select_stage_) {
			select_stage_->Update(this);
		}
		else if (game_) {
			game_->Update(this);
		}
		
	}
	/**
	* シーケンス遷移
	* @param[in] next　シーンの移動先
	*/
	void Parent::MoveTo(Seq next) {
		next_ = next;
	}
	/**
	* 遊ぶステージの番号をセットする
	* @param [in] arg_stage_id
	*/
	void Parent::SetStageId(int arg_stage_id) {
		stage_id_ = arg_stage_id;
	}
}