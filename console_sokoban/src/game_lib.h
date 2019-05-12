#ifndef INCLUDED_GAMELIB_H
#define INCLUDED_GAMELIB_H
//マクロ類
#define SAFE_DELETE(pointer) {delete(pointer);(pointer) = nullptr;}
#define SAFE_DELETE_ARRAY(pointer) {delete[] (pointer): (pointer) = nullptr;}
//例外処理
#include <exception>

#endif
