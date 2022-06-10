#include <iostream>
#include <cmath>

double calculatingVectorLength(double x, double y, double z){
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

int main(){
    double x = 0, y = 0, z = 0;

    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;
    std::cout << "Enter z: ";
    std::cin >> z;

    std::cout << "Length of vector = " << calculatingVectorLength(x, y, z) << std::endl;

    return EXIT_SUCCESS;
}