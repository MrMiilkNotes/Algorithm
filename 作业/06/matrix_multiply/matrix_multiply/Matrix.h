#pragma once
#include<memory>
#include<vector>

/*
������
	�����ӦҪ������ݽ��г�ʼ��
	������
		�˷�
		��ȡ����
		��ȡ����
		����
		��ѯ
*/

template<typename _data_Tp>
class Matrix
{
public:
	typedef std::vector<_data_Tp> mat_row_Tp;
	typedef std::vector<std::vector<_data_Tp>> mat_Tp;
public:
	Matrix(const mat_Tp& data)
		:data_ptr(new mat_Tp(data))
	{  }
	Matrix(mat_Tp* data)
		:data_ptr(data)
	{  }

	//�˷�
	std::shared_ptr<Matrix<_data_Tp>> mult(std::shared_ptr<Matrix<_data_Tp>>&);
	//���ö�Ӧλ��(i, j)��ֵ
	void set(int i, int j, const _data_Tp& _d) { (*data_ptr)[i][j] = _d; }
	//��ȡ��Ӧλ��(i, j)��ֵ
	const _data_Tp& get(int i, int j) const { return (*data_ptr)[i][j]; }
	//��������
	int row() const { return data_ptr->size(); }
	//��������
	int col() const { return (*data_ptr)[0].size(); }
private:
	Matrix();
	std::unique_ptr<mat_Tp> data_ptr;
};


template<typename _data_Tp>
inline std::shared_ptr<Matrix<_data_Tp>>
Matrix<_data_Tp>::mult(std::shared_ptr<Matrix<_data_Tp>>& mat)
{
	std::shared_ptr<Matrix<_data_Tp>> mat_ = 
		std::make_shared<Matrix<_data_Tp>>(new Matrix<_data_Tp>::mat_Tp(this->row(), Matrix<_data_Tp>::mat_row_Tp(mat->col(), 0.0f)));
	for (int i = 0; i != data_ptr->size(); ++i) {
		for (int j = 0; j != mat->col(); ++j) {
			_data_Tp tmp = 0;
			for (int k = 0; k != mat->row(); ++k) {
				tmp += (*data_ptr)[i][k] * mat->get(k, j);
			}
			mat_->set(i, j, tmp);
		}
	}
	return mat_;
}