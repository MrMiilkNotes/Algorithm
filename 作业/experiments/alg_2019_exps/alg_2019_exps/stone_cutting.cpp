#include<iostream>
#include<fstream>
#include<array>
#include<vector>
#include<utility>
#include<algorithm>


typedef std::pair<int, int> sub_stone_t;
typedef std::vector<sub_stone_t> sub_stones_t;	//记录砖块摆放
typedef std::vector<int> stone_col;
typedef std::vector<stone_col> stone_t;

void stone_cutting()
{
	int big_stone_size_w, big_stone_size_l;
	std::cout << "size of stone to cut: ";
	std::cin >> big_stone_size_w >> big_stone_size_l;

	stone_t big_stone(big_stone_size_w + 1, stone_col(big_stone_size_l + 1, 0));

	std::ifstream stones_is("stones.txt");
	int stone_size_w, stone_size_l;
	sub_stones_t sub_stones;
	int min_w = 2 << 20, min_l = 2 << 20;
	while (stones_is >> stone_size_w >> stone_size_l) {
		if (stone_size_w > big_stone_size_w || stone_size_l > big_stone_size_l) { break; }
		if (stone_size_w < min_w) { min_w = stone_size_w; }
		if (stone_size_l < min_l) { min_l = stone_size_l; }
		sub_stones.push_back(sub_stone_t(stone_size_w, stone_size_l));
		big_stone[stone_size_w][stone_size_l] = stone_size_w * stone_size_l;
	}

	for (int i = min_l; i <= big_stone_size_l; ++i) {
		for (int j = min_w; j <= big_stone_size_w; ++j) {
			if (big_stone[j][i] == 0) {							//没有石块能正好摆进去
				for (auto stone : sub_stones) {					//遍历所有子石块
					if (stone.first <= j && stone.second <= i) {//可放入
						int area = std::max(
							big_stone[j - stone.first][i] + big_stone[stone.first][i - stone.second],
							big_stone[j][i - stone.second] + big_stone[j - stone.first][stone.second]
						) + stone.first * stone.second;
						if (area > big_stone[j][i]) {			//且比当前记录的摆放还好
							big_stone[j][i] = area;
						}
					}
				}
			}
		}
	}

	std::cout << "usage rate : " 
		<< float(big_stone[big_stone_size_w][big_stone_size_l]) / (big_stone_size_w * big_stone_size_l) 
		<< std::endl;
}