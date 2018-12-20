#ifndef INCLUDED_DUNGEON_TEMPLATE_LIBRARY_FRACTAL_ISLAND
#define INCLUDED_DUNGEON_TEMPLATE_LIBRARY_FRACTAL_ISLAND
//:::::----------::::::::::----------::::://
//     Dungeon Template Library     //
//          Made by Gaccho.          //
// This code is licensed under CC0.  //
//:::::----------::::::::::----------::::://

#include <stddef.h>
#include <stdint.h>
#include "DungeonRandom.h"

//�`�����N����
void worldMapMake(const int x_, const int y_, const int size_, const int t1_, const int t2_, const int t3_, const int t4_, int map_[17][17], const int max_value_) {
	//�ċN�̏I������
	if (size_ == 0) return;
	//���_�̍��������߂�
	const int vertex_height = ((t1_ + t2_ + t3_ + t4_) / 4) + dungeonRand1(size_);
	map_[x_][y_] = ((vertex_height >= max_value_) ? max_value_ : vertex_height);
	//�l�p�`��2�_���m�̒��_�̍���������
	const int s1=((t1_ + t2_) / 2);
	const int s2=((t1_ + t3_) / 2);
	const int s3=((t2_ + t4_) / 2);
	const int s4=((t3_ + t4_) / 2);
	//4�̒n�_�̍��W�����߂�
	map_[x_ + size_][y_] = s3;
	map_[x_ - size_][y_] = s2;
	map_[x_][y_ + size_] = s4;
	map_[x_][y_ - size_] = s1;

	//�����T�C�Y�𔼕��ɂ���
	const int size = size_ / 2;
	//4�ɕ���
	worldMapMake(x_ - size, y_ - size, size, t1_, s1, s2, map_[x_][y_], map_, max_value_);
	worldMapMake(x_ + size, y_ - size, size, s1, t2_, map_[x_][y_], s3, map_, max_value_);
	worldMapMake(x_ - size, y_ + size, size, s2, map_[x_][y_], t3_, s4, map_, max_value_);
	worldMapMake(x_ + size, y_ + size, size, map_[x_][y_], s3, s4, t4_, map_, max_value_);
}
//�`�����N�����̌Ăяo���E���s
void worldMapSimple(int map_[17][17], const int max_value_) {
	worldMapMake(8, 8, 8, map_[0][0], map_[16][0], map_[0][16], map_[16][16], map_, max_value_);
}

//���[���h�}�b�v����
void createFractalIsland2(int** world_map, const int x_, const int y_, unsigned int seed_, const int max_value_) {
	if (seed_ == 0) seed_ = (unsigned int)dungeonRand1(0xffff);
	int map_[17][17] = { 0 };

	const unsigned int chunk_y = (unsigned int)(y_ / 16);
	const unsigned int chunk_x = (unsigned int)(x_ / 16);

	const unsigned int aslib_world_make_seed1 = 0x3220;
	const unsigned int aslib_world_make_seed2 = 0x292;

	for (unsigned int i = 0; i < chunk_y; ++i)
		for (unsigned int j = 0; j < chunk_x; ++j) {
			//�l�p�`��4�_�̍���������
			dungeonSeed1((unsigned int)(seed_ + i + (j * aslib_world_make_seed1) + ((i^j) * aslib_world_make_seed2)));
			map_[0][0] = dungeonRand1(max_value_);
			dungeonSeed1((unsigned int)(seed_ + ((i + 1) % chunk_y) + (j * aslib_world_make_seed1) + ((((i + 1) % chunk_y) ^ j) * aslib_world_make_seed2)));
			map_[16][0] = dungeonRand1(max_value_);
			dungeonSeed1((unsigned int)(seed_ + i + (((j + 1) % chunk_x) * aslib_world_make_seed1) + ((i ^ ((j + 1) % chunk_x)) * aslib_world_make_seed2)));
			map_[0][16] = dungeonRand1(max_value_);
			dungeonSeed1((unsigned int)(seed_ + ((i + 1) % chunk_y) + (((j + 1) % chunk_x) * aslib_world_make_seed1) + ((((i + 1) % chunk_y) ^ ((j + 1) % chunk_x)) * aslib_world_make_seed2)));
			map_[16][16] = dungeonRand1(max_value_);

			//�`�����N����
			worldMapSimple(map_, max_value_);
			//���������`�����N�����[���h�}�b�v�ɃR�s�y
			for (unsigned int i2 = 0; i2 < 16; ++i2)
				for (unsigned int j2 = 0; j2 < 16; ++j2)
					world_map[i * 16 + i2][j * 16 + j2] = map_[i2][j2];
		}
}
void createFractalIsland(int** world_map, const int x_, const int y_) {
	createFractalIsland2(world_map, x_, y_, 0, 255);
}
void createFractalIsland1(int** world_map, const int x_, const int y_, unsigned int seed_) {
	createFractalIsland2(world_map, x_, y_, seed_, 255);
}

#endif //Included Dungeon Template Library