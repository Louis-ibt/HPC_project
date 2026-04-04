/**
 * pp2_test_linalg.cpp
 * ====================
 * Principal Program 2: Test Vector, Matrix, Point  with overloaded +, =, <<
 */

#include <iostream>
#include "linear_algebra.hpp"

int main()
{
    std::cout << "===========================================\n";
    std::cout << "  PP2 - Point / Vector / Matrix operators  \n";
    std::cout << "===========================================\n\n";

    // -- Point -----------------------------------------------
    std::cout << "-- Point -----------------------------------\n";
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, 5.0, 6.0);
    Point p3 = p1 + p2;
    std::cout << "  p1       = " << p1 << "\n";
    std::cout << "  p2       = " << p2 << "\n";
    std::cout << "  p1 + p2  = " << p3 << "\n\n";

    // -- Vector ----------------------------------------------
    std::cout << "-- Vector ----------------------------------\n";
    Vector v1({1.0, 2.0, 3.0, 4.0});
    Vector v2({10.0, 20.0, 30.0, 40.0});
    Vector v3 = v1 + v2;
    std::cout << "  v1       = " << v1 << "\n";
    std::cout << "  v2       = " << v2 << "\n";
    std::cout << "  v1 + v2  = " << v3 << "\n";

    // Construct from Point
    Vector vp(p1);
    std::cout << "  Vector(p1) = " << vp << "\n\n";

    // -- Matrix ----------------------------------------------
    std::cout << "-- Matrix ----------------------------------\n";
    Matrix M1(3, 3, 1.0);
    Matrix M2(3, 3, 2.0);
    // Give M2 a diagonal pattern
    for (std::size_t i = 0; i < 3; i++) M2[i][i] = 5.0;
    std::cout << "  M1:\n" << M1;
    std::cout << "  M2:\n" << M2;
    Matrix M3 = M1 + M2;
    std::cout << "  M1 + M2:\n" << M3;

    // -- Assignment ------------------------------------------
    std::cout << "\n-- Assignment operator -----------------------\n";
    Matrix M4(3, 3, 0.0);
    M4 = M3;
    std::cout << "  M4 (copy of M3):\n" << M4;

    // -- Read Gp adjacency matrix from file (if present) ------
    std::cout << "\n-- Read Gp adjacency matrix from file -------------\n";
    try {
        Matrix A = Matrix::read_int_file("../outputs/Exercise1_Python/Gp_adjacency_matrix.txt");
        std::cout << A;
    } catch (std::exception &e) {
        std::cout << "  (skipped: " << e.what() << ")\n";
    }

    return 0;
}
