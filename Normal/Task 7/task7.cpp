#include <iostream>
#include <cmath>

// Returns cubic root from value as double in parameter of function
double cubicRoot(const double number, double y0, double yi){
    while(true){
        yi = 0.5 * (y0 + 3 * number / (2 * y0 * y0 + number / y0));

        if(abs(yi - y0) < pow(10.0, -5.0))
            break;

        y0 = yi;
    }

    return yi;
}

// Main function
int main(int argc, char* argv[]){
    double number {}, y0 {}, yi {};

    std::cout << "Enter number: ";
    std::cin >> number;
    y0 = number;

    std::cout << "Result is: " << cubicRoot(number, y0, yi) << std::endl;

    return EXIT_SUCCESS;
}
