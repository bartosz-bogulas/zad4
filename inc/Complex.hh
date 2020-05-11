#ifndef ZAD3_COMPLEX_HH
#define ZAD3_COMPLEX_HH

#include <iostream>
#include <cmath>
#include <sstream>

/* mowiac liczba mam na mysli liczba zespolona */

/**
 * Klasa reprezentujaca liczbe zespolona nad cialem T
 * @tparam T
 */
template <class T>
class Complex {
public:
    T real;
    T imaginary;

    /**
     * Tworzy liczbe z podanych wartosci
     * @param real
     * @param imaginary
     */
    Complex(T real, T imaginary = 0);

    /**
     * Tworzy liczbe (0, 0)
     */
    Complex() = default;

    /**
     * Wylicza wartosc bezwzgledna
     * @return wartosc
     */
    double abs() const;

    /**
     * Sprzezenie liczby
     * @return sprzezona liczbe
     */
    Complex<T> conjugate() const;

    /**
     * Operator dodawania liczb
     * @param complex
     * @return liczba
     */
    Complex<T> operator+(const Complex<T>& complex) const;

    /**
     * Operator odejmowania liczb
     * @param complex
     * @return liczba
     */
    Complex<T> operator-(const Complex<T>& complex) const;

    /**
     * Operator mnozenia liczb
     * @param complex
     * @return liczba
     */
    Complex<T> operator*(const Complex<T>& complex) const;

    /**
     * Operator dzielenia liczb
     * @param complex
     * @return liczba
     */
    Complex<T> operator/(const Complex<T>& complex) const;

    /**
     * Operator dodawania z przypisaniem liczb
     * @param complex
     * @return referencje na liczbe
     */
    Complex<T>& operator+=(const Complex<T>& complex);

    /**
     * Operator mnozenia liczby przez skalar
     * @param complex
     * @return liczba
     */
    Complex<T> operator*(T value) const;

    /**
     * Operator dzielenia liczby przez skalar
     * @param complex
     * @return liczba
     */
    Complex<T> operator/(T value) const;

    /* niezalezna templatka, zeby uniknac problemow kompilacji */

    /**
     * Przeladowany operator wejscia
     * @param in
     * @param complex
     */
    template <class _T>
    friend std::istream& operator>>(std::istream& in, Complex<_T>& complex);

    /**
     * Przeladowany operator wyjscia
     * @param out
     * @param complex
     */
    template <class _T>
    friend std::ostream& operator<<(std::ostream& out, const Complex<_T>& complex);

private:
    static const char opening_parenthesis = '('; /** Znak nawiasu otwierajacego */
    static const char closing_parenthesis = ')'; /** Znak nawiasu zamykajacego */
    static const char i = 'i'; /** Znak reprezentujacy komponent urojony */
};

template <class T>
Complex<T>::Complex(T real, T imaginary) : real(real), imaginary(imaginary) {}

template <class T>
double Complex<T>::abs() const {
    return std::sqrt(std::pow(real, 2) + std::pow(imaginary, 2));
}

template <class T>
Complex<T> Complex<T>::conjugate() const {
    return Complex<T>(real, imaginary * (-1));
}

template <class T>
Complex<T> Complex<T>::operator+(const Complex<T> &complex) const {
    return Complex<T>(real + complex.real, imaginary + complex.imaginary);
}

template <class T>
Complex<T> Complex<T>::operator-(const Complex<T> &complex) const {
    return Complex<T>(real - complex.real, imaginary - complex.imaginary);
}

template <class T>
Complex<T> Complex<T>::operator*(const Complex<T> &complex) const {
    return Complex<T>(
            real * complex.real - imaginary * complex.imaginary,
            real * complex.imaginary + imaginary * complex.real
    );
}

template <class T>
Complex<T> Complex<T>::operator/(const Complex<T> &complex) const {
    return ((*this) * complex.conjugate()) / std::pow(complex.abs(), 2);
}

template <class T>
Complex<T>& Complex<T>::operator+=(const Complex<T> &complex) {
    real += complex.real;
    imaginary += complex.imaginary;
    return *this;
}

template <class T>
Complex<T> Complex<T>::operator*(const T value) const {
    return Complex<T>(
            real * value, imaginary * value
    );
}

template <class T>
Complex<T> Complex<T>::operator/(const T value) const {
    return Complex<T>(
            real / value, imaginary / value
    );
}

template <class T>
std::istream& operator>>(std::istream& in, Complex<T>& complex) {
    char opening_parenthesis, closing_parenthesis, i;

    if (!(in >> opening_parenthesis))
        return in;

    if (opening_parenthesis != Complex<T>::opening_parenthesis) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!(in >> complex.real))
        return in;

    /* zgodnie ze stackoverflow cin czasem zle czyta double jesli po nim jest char (niebialy znak) */

    std::stringstream ss;

    while (true) {
        if (!(in >> i))
            return in;

        if (i == Complex<T>::i)
            break;

        ss << i;
    }

    if (!(ss >> complex.imaginary))
        return in;

    if (!(in >> closing_parenthesis))
        return in;

    if (closing_parenthesis != Complex<T>::closing_parenthesis)
        in.setstate(std::ios::failbit);

    return in;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Complex<T>& complex) {
    out << Complex<T>::opening_parenthesis;
    out << std::noshowpos << complex.real;
    out << std::showpos << complex.imaginary;
    out << std::noshowpos;
    out << Complex<T>::i;
    out << Complex<T>::closing_parenthesis;
    return out;
}

#endif //ZAD3_COMPLEX_HH
