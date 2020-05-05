#ifndef ZAD3_MATRIX_HH
#define ZAD3_MATRIX_HH

#include <iostream>
#include <cmath>

#include "../inc/Complex.hh"
#include "../inc/Vector.hh"

#undef minor // jakis problem na ubuntu, ktorego nie ma na macu

template <class T, size_t size>
class Matrix {

public:
    explicit Matrix(T scalar);
    Matrix() = default;

    T det() const;
    Matrix<T, size> transpose() const;
    Matrix<T, size> replace_column(const Vector<T, size>& vector, size_t j) const;

    Vector<T, size> operator*(const Vector<T, size>& vector) const;

    T operator()(size_t x, size_t y) const;
    T& operator()(size_t x, size_t y);

    Vector<T, size> operator[](size_t x) const;
    Vector<T, size>& operator[](size_t x);

    Vector<T, size> operator()(size_t x) const;
    Vector<T, size>& operator()(size_t x);

    template <class _T, size_t _size>
    friend std::istream& operator>>(std::istream& in, Matrix<_T, _size>& matrix);
    template <class _T, size_t _size>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<_T, _size>& matrix);

private:
    Vector<T, size> vectors[size];
};

template <class T, size_t size>
struct Operations {
    static Matrix<T, size - 1> minor(const Matrix<T, size>& matrix, size_t i, size_t j) {
        Matrix<T, size - 1> result;

        for (size_t x = 0; x < i; x++)
            for (size_t y = 0; y < j; y++)
                result[x][y] = matrix[x][y];

        for (size_t x = i + 1; x < size; x++)
            for (size_t y = 0; y < j; y++)
                result[x - 1][y] = matrix[x][y];

        for (size_t x = 0; x < i; x++)
            for (size_t y = j + 1; y < size; y++)
                result[x][y - 1] = matrix[x][y];

        for (size_t x = i + 1; x < size; x++)
            for (size_t y = j + 1; y < size; y++)
                result[x - 1][y - 1] = matrix[x][y];

        return result;
    }

    static T det(const Matrix<T, size>& matrix) {
        static constexpr Operations<T, size - 1> operations;

        T result = 0;
        for (size_t i = 0; i < size; i++)
            result += (matrix[0][i] * static_cast<double>(std::pow(-1, i)) * operations.det(minor(matrix, 0, i)));

        return result;
    }
};

template <class T>
struct Operations<T, 2> {
    static T det(const Matrix<T, 2>& matrix) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    }
};

template <class T, size_t size>
Matrix<T, size>::Matrix(T scalar) {
    for (size_t i = 0; i < size; i++)
        vectors[i] = Vector<T, size>(scalar);
}

template <class T, size_t size>
T Matrix<T, size>::det() const {
    static constexpr Operations<T, size> operations;
    return operations.det(*this);
}

template <class T, size_t size>
Matrix<T, size>  Matrix<T, size>::transpose() const {
    Matrix<T, size> result;
    for (size_t x = 0; x < size; x++)
        for (size_t y = 0; y < size; y++)
            result[x][y] = vectors[y][x];
    return result;
}

template <class T, size_t size>
Matrix<T, size> Matrix<T, size>::replace_column(const Vector<T, size> &vector, const size_t j) const {
    Matrix<T, size> result;
    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < j; y++)
            result[x][y] = vectors[x][y];

        result[x][j] = vector[x];

        for (size_t y = j + 1; y < size; y++)
            result[x][y] = vectors[x][y];
    }
    return result;
}

template <class T, size_t size>
Vector<T, size> Matrix<T, size>::operator*(const Vector<T, size> &vector) const {
    Vector<T, size> result;
    for (size_t i = 0; i < size; i++)
        result[i] = vectors[i].dot(vector);
    return result;
}

template <class T, size_t size>
T Matrix<T, size>::operator()(const size_t x, const size_t y) const {
    if (x >= size)
        throw std::runtime_error("Index out of range");
    return vectors[x](y);
}

template <class T, size_t size>
T& Matrix<T, size>::operator()(const size_t x, const size_t y) {
    if (x >= size)
        throw std::runtime_error("Index out of range");
    return vectors[x](y);
}

template <class T, size_t size>
Vector<T, size> Matrix<T, size>::operator()(const size_t x) const {
    if (x >= size)
        throw std::runtime_error("Index out of range");
    return vectors[x];
}

template <class T, size_t size>
Vector<T, size>& Matrix<T, size>::operator()(const size_t x) {
    if (x >= size)
        throw std::runtime_error("Index out of range");
    return vectors[x];
}

template <class T, size_t size>
Vector<T, size> Matrix<T, size>::operator[](const size_t x) const {
    return vectors[x];
}

template <class T, size_t size>
Vector<T, size>& Matrix<T, size>::operator[](const size_t x) {
    return vectors[x];
}

template <class T, size_t size>
std::istream& operator>>(std::istream& in, Matrix<T, size>& matrix) {
    for (size_t i = 0; i < size; i++)
        in >> matrix[i];
    return in;
}

template <class T, size_t size>
inline std::ostream& operator<<(std::ostream& out, const Matrix<T, size>& matrix) {
    for (size_t i = 0; i < size; i++) {
        out << matrix[i];
        if (i < size - 1)
            out << "\n";
    }
    return out;
}

using Matrix5d = Matrix<double, 5>;
using Matrix5c = Matrix<Complex<double>, 5>;

#endif //ZAD3_MATRIX_HH
