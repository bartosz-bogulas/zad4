#ifndef ZAD3_MATRIX_HH
#define ZAD3_MATRIX_HH

#include <iostream>
#include <cmath>

#include "../inc/Complex.hh"
#include "../inc/Vector.hh"

/* na niektorych platformach przykrywa uzywana tu nazwe */
#ifdef minor
#undef minor

/**
 * Klasa reprezentujaca macierz dwuwymiarowa o skalarach T i rozmiarze size
 * @tparam T
 * @tparam size
 */
template <class T, size_t size>
class Matrix {

public:
    /**
     * Tworzy macierz o wszystkich skalarach rownych podanemu
     * @param scalar
     */
    explicit Matrix(T scalar);

    /**
     * Tworzy macierz zerowa
     */
    Matrix() = default;

    /**
     * Wylicza wyznacznik
     * @return wartosc
     */
    T det() const;

    /**
     * Transpozycjonuje macierz
     * @return macierz transponowana
     */
    Matrix<T, size> transpose() const;

    /**
     * Podmienia j-ta kolumne macierzy na wektor
     * @param vector
     * @param j
     * @return macierz z podmieniona j-ta kolumna
     */
    Matrix<T, size> replace_column(const Vector<T, size>& vector, size_t j) const;

    /**
     * Operator mnozenia macierzy przez wektor
     * @param vector
     * @return wektor
     */
    Vector<T, size> operator*(const Vector<T, size>& vector) const;

    /**
     * Operator indeksowania macierzy ze sprawdzaniem granic
     * @param x
     * @param y
     * @return skalar na (x, y)-tej pozycji w macierzy
     */
    T operator()(size_t x, size_t y) const;

    /**
     * Operator indeksowania macierzy ze sprawdzaniem granic
     * @param x
     * @param y
     * @return referencja na skalar na (x, y)-tej pozycji w macierzy
     */
    T& operator()(size_t x, size_t y);

    /**
     * Operator indeksowania macierzy
     * @param x
     * @return x-ty wiersz w macierzy jako wektor
     */
    Vector<T, size> operator[](size_t x) const;

    /**
     * Operator indeksowania macierzy
     * @param x
     * @return referencje na x-ty wiersz w macierzy jako wektor
     */
    Vector<T, size>& operator[](size_t x);

    /**
     * Operator indeksowania macierzy ze sprawdzaniem granic
     * @param x
     * @return x-ty wiersz w macierzy jako wektor
     */
    Vector<T, size> operator()(size_t x) const;

    /**
     * Operator indeksowania macierzy ze sprawdzaniem granic
     * @param x
     * @return referencje na x-ty wiersz w macierzy jako wektor
     */
    Vector<T, size>& operator()(size_t x);

    /* niezalezna templatka, zeby uniknac problemow kompilacji */

    /**
     * Przeladowany operator wejscia
     * @param in
     * @param matrix
     */
    template <class _T, size_t _size>
    friend std::istream& operator>>(std::istream& in, Matrix<_T, _size>& matrix);

    /**
     * Przeladowany operator wyjscia
     * @param out
     * @param matrix
     */
    template <class _T, size_t _size>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<_T, _size>& matrix);

private:
    Vector<T, size> vectors[size];
};

/**
 * Operacje na macierzy, przeniesione do struktury, zeby uniknac czesciowej specjalizacji calej klasy Matrix
 * @tparam T
 * @tparam size
 */
template <class T, size_t size>
struct Operations {
    /**
     * Wyznacza minor macierzy usuwajac i-ty wiersz i j-ta kolumne
     * @param matrix
     * @param i
     * @param j
     * @return minor macierzy
     */
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

    /**
     * Wylicza wyznacznik
     * @param matrix
     * @return wartosc
     */
    static T det(const Matrix<T, size>& matrix) {
        static constexpr Operations<T, size - 1> operations;

        T result = 0;
        for (size_t i = 0; i < size; i++)
            result += (matrix[0][i] * static_cast<double>(std::pow(-1, i)) * operations.det(minor(matrix, 0, i)));

        return result;
    }
};

/**
 * Czesciowa specjalizacja powyzszej struktury
 * @tparam T
 */
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

using Matrix5d = Matrix<double, 5>; /** Alias dla macierzy 5x5 liczb rzeczywistych */
using Matrix5c = Matrix<Complex<double>, 5>; /** Alias dla macierzy 5x5 liczb zespolonych */

#endif //ZAD3_MATRIX_HH
