// Task: Calculate the sum of 1/sin1+1/(sin1+sin2)+...1/(sin1+...+sinn), where n is a given natural number.

// Compile:

#include <iostream>
#include <string>
#include <cmath>

// Returns true if string is a number
bool is_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Using 'while' loop to check if all symbols in string are digits
    while (it != __str.end() && std::isdigit(*it))
    {
        // Incrementing iterator
        ++it;
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns 1 / Σsin
double sin_sum(const int &__n)
{
    // Stores sum
    double sum{};

    // Iterating in denominator:
    // sin(1) + sin(2) + sin(3) + ... sin(n)
    for (int i = 1; i <= __n; i++)
    {
        // Σsin
        sum += sin(static_cast<double>(i) * M_PI / 180.0);
    }

    // Returning sum of sin(i)
    return sum;
}

// Returns sum of function y = 1/sin(1)+1/(sin(1)+sin(2))+...1/(sin(1)+sin(2)+sin(3)+...+sin(n))
double sum_of_func(const int &__n)
{
    // Stores future sum of elements from function
    double sum{};

    for (int i = 1; i <= __n; i++)
    {
        sum += 1 / sin_sum(i);
    }

    // Returning sum of certain function
    return sum;
}

int main()
{

    // User's input string
    std::string input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << "Enter size of array: ";
        std::cin >> input;

        // If 'matrix_size' variable is numeric -> break loop
        if (is_number(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not a number value. Try again. \n";
    }

    // Variable to store 'n' in integer representation
    int n{std::stoi(input)};

    std::cout << "Result of sum: " << sum_of_func(n) << std::endl;

    return EXIT_SUCCESS;
}
