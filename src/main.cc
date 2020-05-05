#include "../inc/Complex.hh"
#include "../inc/LinearEquation.hh"

using LinearEquation8d = LinearEquation<double, 8>;
using LinearEquation8c = LinearEquation<Complex<double>, 8>;

int main(int argc, char** argv) {
    char field;
    std::cin >> field;

    switch (field) {
        case 'r' : {
            LinearEquation8d equation;

            std::cout << "Uklad rownan liniowych o wspolczynnikach rzeczywistych" << std::endl;
            std::cout << "Macierz A^T:" << std::endl;

            std::cin >> equation.factor_matrix;
            equation.factor_matrix = equation.factor_matrix.transpose();

            std::cout << "Wektor wyrazow wolnych b:" << std::endl;
            std::cin >> equation.result_vector;

            equation.solve();

            std::cout << "Rozwiazanie x = (x1, x2, x3, x4, x5):" << std::endl;
            std::cout << equation.unknown_vector << std::endl;

            std::cout << "Wektor bledu: Ax-b:" << std::endl;
            std::cout << equation.error_vector << std::endl;
        }
        break;
        case 'z' : {
            LinearEquation8c equation;

            std::cout << "Uklad rownan liniowych o wspolczynnikach zespolonych" << std::endl;
            std::cout << "Macierz A^T:" << std::endl;

            std::cin >> equation.factor_matrix;
            equation.factor_matrix = equation.factor_matrix.transpose();

            std::cout << "Wektor wyrazow wolnych b:" << std::endl;
            std::cin >> equation.result_vector;

            equation.solve();

            std::cout << "Rozwiazanie x = (x1, x2, x3, x4, x5):" << std::endl;
            std::cout << equation.unknown_vector << std::endl;

            std::cout << "Wektor bledu: Ax-b:" << std::endl;
            std::cout << equation.error_vector << std::endl;
        }
        break;
        default:
            std::cout << "Nie rozpoznane cialo liczb" << std::endl;
    }
}
