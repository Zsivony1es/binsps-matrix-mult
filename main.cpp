#include "src/Matrix.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath> 

int main(int argc, char *argv[])
{
    Matrix<15,30,bool> m(0);

    std::cout << m.to_string();

    return 0;
}