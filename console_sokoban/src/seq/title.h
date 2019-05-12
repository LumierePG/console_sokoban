/**
* @file title.h
* タイトルの実装 src/seq/title.h
* @details タイトルの実装を行う
* @author YouTE
* @date 2019/05/06
*/
#pragma once

namespace sequence {
	class Parent;
	class Title {
	public:
		void Draw(); ///<描画
		void Update(Parent* parent); ///<更新
	private:

	};
}