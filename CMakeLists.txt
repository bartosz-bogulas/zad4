cmake_minimum_required(VERSION 3.14)
project(zad3)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        zad3
        inc/Vector.hh
        src/main.cc inc/Matrix.hh inc/LinearEquation.hh inc/Complex.hh)
