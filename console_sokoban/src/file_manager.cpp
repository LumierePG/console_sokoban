#include "file_manager.h"
//唯一のインスタンス
FileManager* FileManager::instance = nullptr;
/**
* 処理の始まりに呼ぶ
*/
void FileManager::Create() {
	if (!instance) {
		instance = new FileManager;
	}
}
/**
* 処理の終わりに呼ぶ
*/
void FileManager::Destory() {
	delete instance;
	instance = nullptr;
}
/**
* インスタンスの呼び出し
* @return 呼び出しインスタンスを返す
*/
FileManager* FileManager::GetInstance() {
	return instance;
}
/**
* ファイル読み込み
* @details newした後は呼んだ先で処理する
* @param [in] file_name ファイル名
* @return newしたファイルポインタを返す
*/
std::ifstream* FileManager::ReadFile(std::string file_name) {
	std::ifstream* fin = new std::ifstream;
	fin->open(file_name);
	return fin;
}
/**
* 読み込んで作業をしたら必ず呼ぶ
* @param [out] *fin 解放するnewされたファイルポインタ
* @details newしたデータを削除するため、ReadFileを読んだ後、処理が終わったら必ず呼ぶ。
*/
void FileManager::CloseFile(std::ifstream* fin) {
	fin->close();
	delete fin;
	fin = nullptr;
}