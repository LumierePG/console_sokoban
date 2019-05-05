#include "key_manager.h"
#include <iostream>
//唯一のインスタンス
KeyManager* KeyManager::instance = nullptr;
/**
* 処理の始まりに呼ぶ
*/
void KeyManager::Create() {
	if (!instance) {
		instance = new KeyManager;
	}
}
/**
* 処理の終わりに呼ぶ
*/
void KeyManager::Destory() {
	delete instance;
	instance = nullptr;
}
/**
* インスタンスの呼び出し
* @return 呼び出しインスタンスを返す
*/
KeyManager* KeyManager::GetInstance() {
	return instance;
}
/**
* キー入力の取得
* @return 押されたキーを返す
*/
char KeyManager::GetKey() {
	char ch;
	std::cin >> ch;
	return ch;
}