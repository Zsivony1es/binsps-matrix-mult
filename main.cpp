#include "src/Matrix.cpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath> 

int main(int argc, char *argv[])
{
    Matrix<15, 30, bool> m(true);

    std::cout << m.to_string();

    return 0;
}