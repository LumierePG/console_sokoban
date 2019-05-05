/**
* @file key_manager.h
* キーマネージャークラスの記述"src/key_manager.h"
* @details キー操作はインスタンスを一個だけ生成してそこから使う　
* @author YouTE
* @date 2019/05/05
*/
#pragma once
#include <iostream>

class KeyManager{
public:
	static void Create(); ///<処理の始まりに呼ぶ
	static void Destory(); ///<処理の終わりに呼ぶ
	static KeyManager* GetInstance(); ///<キーインスタンス呼び出し

	char GetKey(); ///<キー入力の取得

private:
	static KeyManager* instance; ///<唯一のインスタンス

	///シングルトン
	KeyManager() {};
	KeyManager(const KeyManager& obj) {};
	~KeyManager() {};
};
