#ifndef ZAD3_VECTOR_HH
#define ZAD3_VECTOR_HH

#include <iostream>
#include <cmath>

#include "../inc/Complex.hh"

/**
 * Klasa reprezentujaca wektor o skalarach T i rozmiarze size
 * @tparam T
 * @tparam size
 */
template <class T, size_t size>
class Vector {

public:
    /**
     * Tworzy wektor o wszystkich skalarach rownych podanemu
     * @param scalar
     */
    explicit Vector(T scalar);

    /**
     * Tworzy wektor zerowy
     */
    Vector() = default;

    /**
     * Wylicza iloczyn skalarny
     * @param vector
     * @return wartosc
     */
    T dot(const Vector<T, size>& vector) const;

    /**
     * Operator dodawania wektorow
     * @param vector
     * @return wektor
     */
    Vector<T, size> operator+(const Vector<T, size>& vector) const;

    /**
     * Operator odejmowania wektorow
     * @param vector
     * @return wektor
     */
    Vector<T, size> operator-(const Vector<T, size>& vector) const;

    /**
     * Operator mnozenia wektora przez skalar
     * @param scalar
     * @return wektor
     */
    Vector<T, size> operator*(T scalar) const;

    /**
     * Operator dzielenia wektora przez skalar
     * @param scalar
     * @return wektor
     */
    Vector<T, size> operator/(T scalar) const;

    /**
     * Operator indeksowania wektora
     * @param i
     * @return skalar na i-tej pozycji w wektorze
     */
    T operator[](size_t i) const;

    /**
     * Operator indeksowania wektora
     * @param i
     * @return referencje na skalar na i-tej pozycji w wektorze
     */
    T& operator[](size_t i);

    /**
     * Operator indeksowania wektora ze sprawdzaniem granic
     * @param i
     * @return skalar na i-tej pozycji w wektorze
     */
    T operator()(size_t i) const;

    /**
     * Operator indeksowania wektora ze sprawdzaniem granic
     * @param i
     * @return referencje na skalar na i-tej pozycji w wektorze
     */
    T& operator()(size_t i);

    /* niezalezna templatka, zeby uniknac problemow kompilacji */

    /**
     * Przeladowany operator wejscia
     * @param in
     * @param vector
     */
    template <typename _T, size_t _size>
    friend std::istream& operator>>(std::istream& in, Vector<_T, _size>& vector);

    /**
     * Przeladowany operator wyjscia
     * @param in
     * @param vector
     */
    template <typename _T, size_t _size>
    friend std::ostream& operator<<(std::ostream& out, const Vector<_T, _size>& vector);

private:
    T scalars[size];
};

template <class T, size_t size>
Vector<T, size>::Vector(T scalar) {
    for (size_t i = 0; i < size; i++)
        scalars[i] = scalar;
}

template <class T, size_t size>
T Vector<T, size>::dot(const Vector<T, size>& vector) const {
    T result = 0;
    for (size_t i = 0; i < size; i++)
        result += scalars[i] * vector.scalars[i];
    return result;
}

template <class T, size_t size>
T Vector<T, size>::operator[](const size_t i) const {
    return scalars[i];
}

template <class T, size_t size>
T& Vector<T, size>::operator[](const size_t i) {
    return scalars[i];
}

template <class T, size_t size>
T Vector<T, size>::operator()(const size_t i) const {
    if (i >= size)
        throw std::runtime_error("Index out of range");
    return scalars[i];
}

template <class T, size_t size>
T& Vector<T, size>::operator()(const size_t i) {
    if (i >= size)
        throw std::runtime_error("Index out of range");
    return scalars[i];
}

template <class T, size_t size>
Vector<T, size> Vector<T, size>::operator+(const Vector<T, size> &vector) const {
    Vector<T, size> result;
    for (size_t i = 0; i < size; i++)
        result.scalars[i] = scalars[i] + vector.scalars[i];
    return result;
}

template <class T, size_t size>
Vector<T, size> Vector<T, size>::operator-(const Vector<T, size> &vector) const {
    Vector<T, size> result;
    for (size_t i = 0; i < size; i++)
        result.scalars[i] = scalars[i] - vector.scalars[i];
    return result;
}

template <class T, size_t size>
Vector<T, size> Vector<T, size>::operator*(T scalar) const {
    Vector<T, size> result;
    for (size_t i = 0; i < size; i++)
        result.scalars[i] = scalars[i] * scalar;
    return result;
}

template <class T, size_t size>
Vector<T, size> Vector<T, size>::operator/(T scalar) const {
    Vector<T, size> result;
    for (size_t i = 0; i < size; i++)
        result.scalars[i] = scalars[i] / scalar;
    return result;
}

template <class T, size_t size>
std::istream& operator>>(std::istream& in, Vector<T, size>& vector) {
    for (size_t i = 0; i < size; i++)
        in >> vector.scalars[i];
    return in;
}

template <class T, size_t size>
std::ostream& operator<<(std::ostream& out, const Vector<T, size>& vector) {
    for (size_t i = 0; i < size; i++) {
        out << vector.scalars[i];
        if (i < size - 1)
            out << " ";
    }
    return out;
}

using Vector5d = Vector<double, 5>; /** Alias dla wektora 5 liczb rzeczywistych */
using Vector5c = Vector<Complex<double>, 5>; /** Alias dla wektora 5 liczb zespolonych */

#endif //ZAD3_VECTOR_HH
