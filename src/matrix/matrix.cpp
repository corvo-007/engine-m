#include "matrix/matrix.h"
#include "utils.h"

namespace MathEngine {

    Matrix::Matrix(): matrix{} {

    }

    Matrix::Matrix(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i): matrix{{a, b, c}, {d, e, f}, {g, h, i}} {

    }

    Matrix::Matrix(const float matrix[3][3]) {
        copy(matrix);
    }

    Matrix::Matrix(const Matrix &mat) {
        copy(mat.matrix);
    }

    void Matrix::copy(const float matrix[3][3]) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this -> matrix[i][j] = matrix[i][j];
            }
        }
    }

    float Matrix::determinant() const {
        return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }

    Matrix& Matrix::operator=(const Matrix &mat) {
        copy(mat.matrix);
        return *this;
    }

    float* Matrix::operator[](const int i) {
        return matrix[i];
    }

    const float* Matrix::operator[](const int i) const {
        return matrix[i];
    }

    Matrix Matrix::operator+(const Matrix &mat) const {
        Matrix m;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = matrix[i][j] + mat[i][j];
            }
        }
        return m;
    }

    Matrix& Matrix::operator+=(const Matrix &mat) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] += mat[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &mat) const {
        Matrix m;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = matrix[i][j] - mat[i][j]; 
            }
        }
        return m;
    }

    Matrix& Matrix::operator-=(const Matrix &mat) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] -= mat[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator*(const float k) const {
        Matrix m;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = matrix[i][j] * k;
            }
        }
        return m;
    }

    Matrix& Matrix::operator*=(const float k) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] *= k;
            }
        }
        return *this;
    }

    Matrix Matrix::operator/(float k) const {
        k = 1 / k;
        return (*this) * k;
    }

    Matrix& Matrix::operator/=(float k) {
        k = 1 / k;
        return (*this) *= k;
    }

    Matrix Matrix::operator*(const Matrix &mat) const {
        Matrix m;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    m[i][j] += matrix[i][k] * mat[k][j];
                }
            }
        }
        return m;
    }

    Matrix& Matrix::operator*=(const Matrix &mat) {
        (*this) = (*this) * mat;
        return *this;
    }

    Vector3d Matrix::operator*(const Vector3d &vec) const {
	    return {matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z, matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z, matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z};
    }

    bool Matrix::operator==(const Matrix &mat) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!equals(matrix[i][j], mat[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix &mat) const {
        return !((*this) == mat);
    }

    bool Matrix::getInverse(Matrix &mat) const {
        float det = determinant();

        if (det == 0.0) {
            return false;
        }

        float oneOverDet = 1 / det;

        mat[0][0] = oneOverDet * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
        mat[0][1] = -oneOverDet *  (matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
        mat[0][2] = oneOverDet * (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]);
        mat[1][0] = -oneOverDet *  (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
        mat[1][1] = oneOverDet * (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]);
        mat[1][2] = -oneOverDet *  (matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
        mat[2][0] = oneOverDet * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        mat[2][1] = -oneOverDet *  (matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
        mat[2][2] = oneOverDet * (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);

        return true;
    }

    bool Matrix::inverse() {
        Matrix mat;
        bool i = getInverse(mat);
        (*this) = mat;
        return i;
    }

    Matrix Matrix::getTranspose() const {
        Matrix m;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[j][i] = matrix[i][j];
            }
        }
        return m;
    }

    Matrix& Matrix::transpose() {
        (*this) = getTranspose();
        return *this;
    }

    Matrix Matrix::identity() {
        return {1, 0, 0, 0, 1, 0, 0, 0, 1};
    }
}
