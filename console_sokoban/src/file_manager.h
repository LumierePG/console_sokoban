/**
* @file file_manager.h
* ファイルマネージャークラスの記述"src/file_manager.h"
* @details ファイルの扱いはインスタンスを一個だけ生成してそこから使用
* @author YouTE
* @date 2019/05/02
*/
#pragma once
#include <fstream>
#include <string>

class FileManager {
public:
	static void Create(); ///<処理の始まりに呼ぶ
	static void Destory(); ///<処理の終わりに呼ぶ
	static FileManager* GetInstance(); ///<ファイルマネージャークラスにアクセスする唯一の関数

	const std::string ReadFile(const std::string& file_name);///<ファイルを読み込む
	const std::string ReadMapFile(const std::string& file_name);///<ファイルを読み込む
private:
	static FileManager* instance; ///<唯一のインスタンス
	///シングルトン
	FileManager() {};
	FileManager(const FileManager& obj) {};
	~FileManager() {};
};
