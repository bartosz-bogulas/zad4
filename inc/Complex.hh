#ifndef ZAD3_COMPLEX_HH
#define ZAD3_COMPLEX_HH

#include <iostream>
#include <cmath>
#include <sstream>

template <class T>
class Complex {
public:
    T real;
    T imaginary;

    Complex(T real, T imaginary = 0);
    Complex() = default;

    double abs() const;
    Complex<T> conjugate() const;

    Complex<T> operator+(const Complex<T>& complex) const;
    Complex<T> operator-(const Complex<T>& complex) const;
    Complex<T> operator*(const Complex<T>& complex) const;
    Complex<T> operator/(const Complex<T>& complex) const;

    Complex<T>& operator+=(const Complex<T>& complex);

    Complex<T> operator*(T value) const;
    Complex<T> operator/(T value) const;

    template <class _T>
    friend std::istream& operator>>(std::istream& in, Complex<_T>& complex);
    template <class _T>
    friend std::ostream& operator<<(std::ostream& out, const Complex<_T>& complex);

private:
    static const char opening_parenthesis = '(';
    static const char closing_parenthesis = ')';
    static const char i = 'i';
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

    // according to stackoverflow cin does not always read double followed by a char properly

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
