// Task: Create a program for tabulating the function 'y = [cotan(lnx)]^2' on interval [a, b] with 'h' step

// Compile: gcc task20.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra -lm

#include <iostream>
#include <iomanip>
#include <cmath>

// Returns calculated value from this function 'y = [cotan(lnx)]^2'
double func_calc(const int &__x)
{
    return pow((1 / tan(log(static_cast<double>(__x)))), 2);
}

void func_print(const int &__lower, const int &__upper, const int &__step)
{
    std::cout << std::right << 'x' << std::setw(10) << ' ' << 'y' << std::endl;
    
    // Printing calculated values with 'for' loop
    for (int x_value = __lower; x_value <= __upper; x_value += __step)
    {
        std::cout << std::right << x_value << std::setw(10) << ' ' << func_calc(x_value) << '\n';
    }

    // Flushing output stream
    std::cout << std::endl;
}

int main()
{
    // Variables to calculate function:
    // Lower interval, upper interval and step
    int lower{}, upper{}, step{};

    std::cout << "Enter lower interval: ";
    std::cin >> lower;
    std::cout << "Enter upper interval: ";
    std::cin >> upper;
    std::cout << "Enter step: ";
    std::cin >> step;
    
    func_print(lower, upper, step);

    return EXIT_SUCCESS;
}
