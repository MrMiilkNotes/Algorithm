#include<iostream>
#include<vector>
#include<algorithm>

typedef int data_type;

void findLMIS_1(const std::vector<data_type>& seq)
{	//Longest monotonically increasing subsequence
	std::vector<data_type> lmis;
	std::vector<int> length_rec(seq.size(), 1);
	std::vector<int> pre_rec(seq.size(), 0);
	data_type max_len = 0;
	int max_idx = 0;
	for (int i = 1; i != seq.size(); ++i) {
		pre_rec[i] = i;//self, length = 1
		for (int j = i; j != 0; --j) {
			if (seq[j] < seq[i] && length_rec[j] + 1 > length_rec[i]) {
				length_rec[i] = length_rec[j] + 1;
				pre_rec[i] = j;
				if (length_rec[i] > max_len) { 
					max_len = length_rec[i];
					max_idx = i;
				}
			}
		}
	}
	for (int j = 0; j != max_len; ++j) {
		std::cout << seq[max_idx] << ' ';
		max_idx = pre_rec[max_idx];
	}
}

int bi_search(const std::vector<data_type> seq, const data_type& _d, int begin, int end)
{
	if (begin == end) { 
		if (_d > seq[end] && _d < seq[end + 1]) { return end + 1; }
		return -1;
	}
	int spl_idx = (begin + end) / 2;
	if (_d > seq[spl_idx] && _d < seq[spl_idx + 1]) { return spl_idx + 1; }
	else if (_d >= seq[spl_idx]) { return bi_search(seq, _d, spl_idx + 1, end); }
	else { return bi_search(seq, _d, begin, spl_idx); }
}

void findLMIS_2(const std::vector<data_type>& seq)
{
	std::vector<int> B(seq.size(), 100);
	std::vector<int> pre_rec(seq.size(), 0);
	int len = 1, len_idx = 0;

	for (int i = 0; i != seq.size(); ++i) {
		if (seq[i] < B[1]) {
			B[1] = seq[i];//长度为1的最小值
			pre_rec[i] = i;
			len_idx = i;
		}
		else {
			int idx = bi_search(B, seq[i], 1, len);
			if (idx != -1) {//找到了插入位置
				B[idx] = seq[i];
				if (idx > len) {
					len = idx;	//最长子序列长度
					pre_rec[i] = len_idx;//位置记录
					len_idx = i;
				}
				else { pre_rec[i] = pre_rec[idx]; }
			}
		}
	}
	for (int j = len; j != 0; --j) {
		std::cout << seq[len_idx] << ' ';
		len_idx = pre_rec[len_idx];
	}
}

void test6_12()
{
	std::vector<data_type> seq{ 3, 2, 1, 3, 5, 6, 9, 8, 1, 3, 10, 2 };
	findLMIS_2(seq);
}