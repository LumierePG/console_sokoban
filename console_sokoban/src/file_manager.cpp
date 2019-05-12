#include "file_manager.h"
#include "game_lib.h"
#include <sstream>
#include <fstream>
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
* @details 一行ずつ読み込んで読み込み終わったらデータを投げる
* @param [in] file_name ファイル名
* @return 読み込んだデータをstringで返す
*/
const std::string FileManager::ReadFile(const std::string& file_directory) {

	std::ifstream fin(file_directory);
	
	if (!fin) {
		throw("ファイルが読み込めない。");
	}
	std::stringstream stio;
	std::string ss;
	while (std::getline(fin,ss)) {
		stio << ss;
		ss.erase();
	}
	return stio.str();
}
/**
* ファイル読み込み
* @details 一行ずつ読み込んで読み込み終わったらデータを投げる
* @param [in] file_name ファイル名
* @return 読み込んだデータをstringで返す
*/
const std::string FileManager::ReadMapFile(const std::string& file_directory) {

	std::ifstream fin(file_directory);

	if (!fin) {
		throw("ファイルが読み込めない。");
	}
	std::stringstream stio;
	std::string ss;
	while (std::getline(fin, ss)) {
		stio << ss << '\n';
		ss.erase();
	}
	return stio.str();
}
