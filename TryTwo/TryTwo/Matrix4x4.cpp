#include "Matrix4x4.h"

//�޲ι��캯��
Matrix4x4::Matrix4x4() {
    // ��ʼ��Ϊ��λ����
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            data[i][j] = (i == j) ? 1.0f : 0.0f;
}

Matrix4x4::~Matrix4x4() {
    /*empty*/
}

Matrix4x4::Matrix4x4(const Matrix4x4& _other)
{
    *this = _other;
}

//������ʾ����
void Matrix4x4::Show()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << data[i][j] << "   ";
            if (j == 3)
                std::cout << std::endl;
        }
    }
}
//�����ļӼ���
Matrix4x4 Matrix4x4::operator+(Matrix4x4& _other)
{
    Matrix4x4 ansMatrix;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ansMatrix.data[i][j] = data[i][j] + _other.data[i][j];
        }
    }
    return ansMatrix;
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4& _other)
{
    Matrix4x4 ansMatrix;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            ansMatrix.data[i][j] = data[i][j] - _other.data[i][j];
        }
    }
    return ansMatrix;
}

// ����˷�
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::LeftCrossProduct(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.data[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.data[i][j] += data[k][j] * other.data[i][k];
            }
        }
    }
    return result;
}

// �����������ĳ˷����任��
Vector4D Matrix4x4::operator*(const Vector4D& vec) const {
    return Vector4D(
        data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * vec.w,
        data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * vec.w,
        data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * vec.w,
        data[3][0] * vec.x + data[3][1] * vec.y + data[3][2] * vec.z + data[3][3] * vec.w
    );
}

//����
void Matrix4x4::Zero()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            data[i][j] = 0;
}
//��Ϊ��λ��
void Matrix4x4::Identity()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            data[i][j] = (i == j) ? 1.0f : 0.0f;
}

Matrix4x4 Matrix4x4::BuildViewPort(float x, float y, float width, float height, float depth)
{
    Matrix4x4 AnsMatrix;
    //����ƽ����
    AnsMatrix.data[0][3] = x + width / 2.0f;
    AnsMatrix.data[1][3] = y + height / 2.0f;
    AnsMatrix.data[2][3] = depth / 2.0f;
    //����������
    AnsMatrix.data[0][0] = width / 2.0f;
    AnsMatrix.data[1][1] = height / 2.0f;
    AnsMatrix.data[2][2] = depth / 2.0f;
    return AnsMatrix;
}