#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>

typedef int data_t;
typedef std::vector<data_t> array_t;


template<typename array_iterator>
void merge(array_iterator base, array_iterator in_1, array_iterator in_2, int size_1, int size_2)
{
	// �鲢���������б�Ϊһ��
	int counter_1 = 0;
	int counter_2 = 0;
	while (counter_1 != size_1 || counter_2 != size_2) {
		if (counter_1 == size_1 || (counter_2 != size_2 && *(in_1 + counter_1) > *(in_2 + counter_2))) {
			*(base++) = *(in_2 + counter_2++);
		}
		else if (counter_2 == size_2 || (counter_1 != size_1 && *(in_2 + counter_2) > *(in_1 + counter_1))) {
			*(base++) = *(in_1 + counter_1++);
		}
	}
}

template<typename array_iterator, typename array_t>
void sort_merge(array_iterator begin, array_iterator end)
{
	if (begin != end) {			//����С��1���б���Ҫ����
		array_t arr_1, arr_2;	//���ڼ�¼�鲢�����е����������б��Ӷ��ϲ�Ϊһ���б�
		int elem_num = end - begin;
		int depth = std::log2(elem_num) + 1;
		for (int i = 0; i != depth; ++i) {	//deepth���ǵݹ��㷨�й鲢����ȣ�����ѭ���ضԲ�ͬ��Ƚ��й鲢
			int lenght = 2 << i;
			int n_iter = elem_num / lenght + 1;
			for (int j = 0; j != n_iter; ++j) {
				auto base = begin + lenght * j;			//���ֹ鲢�б�Ļ�������
				int arr_1_len = std::pow(2, std::log2(lenght) - 1);	//�������б���
				lenght = std::min(lenght, end - base);				//ʣ��Ԫ����Ŀ--Ϊ�˱���Խ�磬�������ó���
				arr_1.clear();										//�������������б�
				arr_2.clear();
				std::copy(base, base + std::min(arr_1_len, lenght), std::back_inserter(arr_1));
				std::copy(base + std::min(arr_1_len, lenght), base + lenght, std::back_inserter(arr_2));
																	//����merge���кϲ�
				merge<array_iterator>(base, arr_1.begin(), arr_2.begin(), arr_1.size(), arr_2.size());
			}
		}
	}
}

void func_hw_5_1()
{
	int len_arr = (2 << 3) + 2;
	array_t test_arr;
	for (int _ = 0; _ != len_arr; ++_) {
		test_arr.push_back(rand());
	}

	sort_merge<array_t::iterator, array_t>(test_arr.begin(), test_arr.end());
	for (int i = 0; i != len_arr; ++i) {
		std::cout << test_arr[i] << ' ';
	}
	std::cout << std::endl;
}