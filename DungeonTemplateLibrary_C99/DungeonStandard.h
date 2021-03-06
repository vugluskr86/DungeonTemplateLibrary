﻿#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_C99_DUNGEON_STANDARD
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_C99_DUNGEON_STANDARD
//:::::----------::::::::::----------::::://
//     Dungeon Template Library     //
//          Made by Gaccho.          //
// This code is licensed under CC0.  //
//:::::----------::::::::::----------::::://

//全てのマスを0で埋める
void dungeonInit(int** stl_, const int x_, const int y_) {
	for (int i = 0; i < y_; ++i)
		for (int j = 0; j < x_; ++j)
			stl_[i][j] = 0;
}
//全てのマスを指定した数値で埋める
void dungeonInit2(int** stl_, const int x_, const int y_, const int value_) {
	for (int i = 0; i < y_; ++i)
		for (int j = 0; j < x_; ++j)
			stl_[i][j] = value_;
}
//値が全て一致しているか確認する
int dungeonArrayCheck(const int** stl_, const int x_, const int y_) {
	if (y_ == 0 || x_ == 0) return 0;
	const int stl_value = stl_[0][0];
	for (int i = 0; i < y_; ++i)
		for (int j = 0; j < x_; ++j)
			if (stl_value != stl_[i][j]) return 0;
	return 1;
}

#endif //Included Dungeon Template Library