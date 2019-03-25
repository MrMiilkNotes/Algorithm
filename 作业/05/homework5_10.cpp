#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>

typedef int data_t;
typedef std::vector<data_t> array_t;

data_t quick_sort_kth_min(int k, array_t arr)
{
	// 边界条件
	if (arr.size() == 0) { return *(new data_t); }
	if (arr.size() == 1) { return arr[0]; }
	//快速排序部分
	data_t flag = arr[0];
	auto s_iter = arr.begin() + 1;
	auto e_iter = arr.end() - 1;
	while (s_iter != e_iter) {
		while (*(s_iter) < flag && s_iter != e_iter) {
			++s_iter;
		}
		while (*(e_iter) > flag && s_iter != e_iter) {
			--e_iter;
		}
		auto tmp = *(s_iter);
		*(s_iter) = *(e_iter);
		*(e_iter) = tmp;
	}

	//利用轴枢的位置和k比较，从而确定找到或者在左边还是右边继续寻找
	if (s_iter - arr.begin() == k) {
		return flag;
	}
	else if (s_iter - arr.begin() < k) {
		array_t tmp;
		std::copy(s_iter, arr.end(), std::back_inserter(tmp));
		return quick_sort_kth_min(k - (s_iter - arr.begin()), tmp);
	}
	else {	// if (s_iter - arr.begin() > k) 
		array_t tmp;
		std::copy(arr.begin() + 1, s_iter, std::back_inserter(tmp));
		return quick_sort_kth_min(k, tmp);
	}
}

void homework510()
{
	int len_arr = (2 << 3) + 2;
	array_t test_arr = {1, 2, 30, 4, 5, 9 ,6, 7, 8};
	/*for (int _ = 0; _ != len_arr; ++_) {
		test_arr.push_back(rand());
	}*/

	std::cout << quick_sort_kth_min(5, test_arr) << std::endl;
}