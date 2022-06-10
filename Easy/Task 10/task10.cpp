#include <iostream>
#include <cmath>
#include <climits>

int main(){
    double x = 0, y = 0;

    std::cout << "Enter x: ";
    std::cin >> x;
    if(x == 0){
        std::cout << "x can't be equals 0. " << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        std::cout << "Enter y: ";
        std::cin >> y;

        if(x < __DBL_MAX__ && y < __DBL_MAX__)
            std::cout << "Result is " << pow((1 - tan(x)), (1 / tan(x))) + cos(x - y) << std::endl;
        else
            std::cout << "Limit of numbers exceed." << std::endl;
    }

    return EXIT_SUCCESS;
}