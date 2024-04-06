#include "src/RandomMatrixGenerator.h"
#include "src/subsrc1/f3.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath> 

int main(int argc, char *argv[])
{
    std::cout << f3(5, 6) << std::endl;
    Matrix<15, 30, bool> m;

    std::cout << m.to_string();

    return 0;
}