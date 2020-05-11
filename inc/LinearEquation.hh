#ifndef ZAD3_LINEAREQUATION_HH
#define ZAD3_LINEAREQUATION_HH

#include <iostream>

#include "../inc/Complex.hh"
#include "../inc/Vector.hh"
#include "../inc/Matrix.hh"

/**
 * Klasa reprezentujaca rownanie liniowe o skalarach T i rozmiarze size
 * @tparam T
 * @tparam size
 */
template <class T, size_t size>
class LinearEquation {
public:
    Vector<T, size> unknown_vector; /** Wektor niewiadomych */
    Vector<T, size> error_vector; /** Wektor bledu */

    Matrix<T, size> factor_matrix; /** Macierz wspolczynnikow */
    Vector<T, size> result_vector; /** Wektor rozwiazan */

    /**
     * Rozwiazuje rownanie liniowe ustawiajac odpowiednie atrybuty klasy
     */
    void solve();
};

template <class T, size_t size>
void LinearEquation<T, size>::solve() {
    const T determinant = factor_matrix.det();

    for (size_t i = 0; i < size; i++)
        unknown_vector[i] = factor_matrix.replace_column(result_vector, i).det() / determinant;

    error_vector = factor_matrix * unknown_vector - result_vector;
}

using LinearEquation5d = LinearEquation<double, 5>; /** Alias dla rownania 5x5 liczb rzeczywistych */
using LinearEquation5c = LinearEquation<Complex<double>, 5>; /** Alias dla rownania 5x5 liczb zespolonych

#endif //ZAD3_LINEAREQUATION_HH
