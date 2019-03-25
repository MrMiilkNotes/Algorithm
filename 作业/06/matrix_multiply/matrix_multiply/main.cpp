#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<time.h>

#include"Matrix.h"

typedef float data_type;
typedef Matrix<data_type> Matrix_t;
typedef typename std::vector<std::shared_ptr<Matrix_t>> Matrixs;

void init_matrix()
{
	std::ofstream output_mat("matrixs_1.txt");
	std::vector<int> matrix_sizes{ 5, 3, 4, 6, 5, 2, 5, 5, 3, 4, 6, 5, 2, 5, 5, 3, 4, 6, 5, 2, 5, 5, 3, 4, 6, 5, 2, 5 };
	std::string _sz, mat;
	for (int i = 0; i != matrix_sizes.size() - 1; ++i) {
		output_mat << matrix_sizes[i] << ' ' << matrix_sizes[i + 1] << '\n';
		for (int j = 0; j != matrix_sizes[i] * matrix_sizes[i + 1]; ++j) {
			output_mat << 2 * (float(rand()) / RAND_MAX) << ' ';
		}
		output_mat << '\n';
	}
	output_mat.close();
}

std::vector<std::string> split(const std::string &str, const std::string &pattern)
{
	std::vector<std::string> res;
	if (str == "")
		return res;
	//在字符串末尾也加入分隔符，方便截取最后一段
	std::string strs = str + pattern;
	size_t pos = strs.find(pattern);

	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(pattern);
	}

	return res;
}

void input_matrix(Matrixs& mats)
{
	std::fstream inp_mat("matrixs_1.txt");
	int row, col;
	std::string line;
	while (std::getline(inp_mat, line))
	{
		std::stringstream line_s(line);
		line_s >> row >> col;
		std::shared_ptr<Matrix_t> mat = 
			std::make_shared<Matrix_t>(new Matrix_t::mat_Tp(row, Matrix_t::mat_row_Tp(col, 0.0f)));
		std::getline(inp_mat, line);
		auto A = split(line, " ");
		for (int i = 0; i != row; ++i) {
			for (int j = 0; j != col; ++j) {
				mat->set(i, j, std::stof(A[i * col + j]));
			}
		}
		mats.push_back(mat);
	}
}

void matrix_chain_dp(Matrix<int>& mult_times, Matrix<int>& solute_rec, const Matrixs& mats)
{
	for (int i = 0; i != solute_rec.row(); ++i) {
		solute_rec.set(i, i, i);
	}
	for (int j = 1; j != mult_times.col(); ++j) {
		for (int i = j - 1; i != -1; --i) {
			mult_times.set(i, j, mult_times.get(i + 1, j) + mats[i]->row() * mats[i]->col() * mats[j]->col());
			solute_rec.set(i, j, i);
			for (int k = i + 1; k != j; ++k) {
				int tmp = mult_times.get(i, k) + mult_times.get(k + 1, j) +
					mats[i]->row() * mats[k]->col() * mats[j]->col();
					if (tmp < mult_times.get(i, j)) {
						mult_times.set(i, j, tmp);
						solute_rec.set(i, j, k);
				}
			}
		}
	}
}

int matrix_chain_memo(Matrix<int>& mult_times, Matrix<int>& solute_rec, const Matrixs& mats, int begin, int end)
{
	if (begin == end) {
		solute_rec.set(begin, end, begin);
		return 0;
	}
	else if (mult_times.get(begin, end) != 0) {
		return mult_times.get(begin, end);
	}
	//else
	mult_times.set(begin, end, 
		matrix_chain_memo(mult_times, solute_rec, mats, begin + 1, end) + mats[begin]->row() * mats[begin]->col() * mats[end]->col());
	solute_rec.set(begin, end, begin);
	for (int k = begin + 1; k != end; ++k) {
		int tmp = matrix_chain_memo(mult_times, solute_rec, mats, begin, k) + 
			matrix_chain_memo(mult_times, solute_rec, mats, k + 1, end) +
			mats[begin]->row() * mats[k]->col() * mats[end]->col();
		if (tmp < mult_times.get(begin, end)) {
			mult_times.set(begin, end, tmp);
			solute_rec.set(begin, end, k);
		}
	}
	return mult_times.get(begin, end);
}

std::shared_ptr<Matrix_t> matrix_mult(Matrix<int>& solute_rec, const Matrixs& mats, int i, int j)
{
	if (i == j) { return mats[j]; }
	auto A = matrix_mult(solute_rec, mats, i, solute_rec.get(i, j));
	auto B = matrix_mult(solute_rec, mats, solute_rec.get(i, j) + 1, j);
	return A->mult(B);
}

int main()
{
	//用随机数生成矩阵
	init_matrix();
	//矩阵输入 
	Matrixs mat_buf;
	input_matrix(mat_buf);
	//乘法方式
	Matrix<int>::mat_Tp init_mat(mat_buf.size(), Matrix<int>::mat_row_Tp(mat_buf.size(), 0));
	Matrix<int> mult_times(init_mat), solute_rec(init_mat);
	auto a = clock();
	//matrix_chain_memo(mult_times, solute_rec, mat_buf, 0, mat_buf.size() - 1);
	matrix_chain_dp(mult_times, solute_rec, mat_buf);
	std::cout << "matrix_chain function using time: " << clock() - a << '\n';
	//乘法计算
	auto C = matrix_mult(solute_rec, mat_buf, 0, mat_buf.size() - 1);
	//输出
	for (int i = 0; i != C->row(); ++i) {
		for (int j = 0; j != C->col(); ++j) {
			std::cout << C->get(i, j) << '\t';
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}