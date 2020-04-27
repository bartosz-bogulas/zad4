#ifndef ZAD3_LINEAREQUATION_HH
#define ZAD3_LINEAREQUATION_HH

#include <iostream>

#include "../inc/Complex.hh"
#include "../inc/Vector.hh"
#include "../inc/Matrix.hh"

template <class T, size_t size>
class LinearEquation {
public:
    Vector<T, size> unknown_vector;
    Vector<T, size> error_vector;

    Matrix<T, size> factor_matrix;
    Vector<T, size> result_vector;

    void solve();
};

template <class T, size_t size>
void LinearEquation<T, size>::solve() {
    const T determinant = factor_matrix.det();

    for (size_t i = 0; i < size; i++)
        unknown_vector[i] = factor_matrix.replace_column(result_vector, i).det() / determinant;

    error_vector = factor_matrix * unknown_vector - result_vector;
}

using LinearEquation5d = LinearEquation<double, 5>;
using LinearEquation5c = LinearEquation<Complex<double>, 5>;

#endif //ZAD3_LINEAREQUATION_HH
