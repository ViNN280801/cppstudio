// Task: The program must find the intersection point of two lines.
// The following equations are given: y = ax^2 + bx + c and y = dx + k.
// As you may have already understood, these are equations of lines, where a, b, c, d, k
// are numbers that are entered from the keyboard. It is necessary to find the value of x.

// So it is necessary to organize the input of numbers from the keyboard.
// After that, substitute the second equation instead of the y into the first one,
// you get an equality that is not difficult to solve. As a result,
// the program should return two numbers: x and y

// Compile: gcc task28.cpp -o main -lstdc++ -lm -Wall -Wpedantic -Wextra

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Returns true if string is a number
bool is_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Using 'while' loop to check if all symbols in string are digits
    while (it != __str.end() && (std::isdigit(*it) || (*it) == '-'))
    {
        // Incrementing iterator
        ++it;
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns user's input value as 'int'
int input(const char *msg)
{
    // User's input string
    std::string input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> input;

        // If 'input' is contains only of digits
        if (is_number(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not a number value. Try again. \n";
    }

    // Returning converted user's inputted value to 'int' type
    return std::stoi(input);
}

// Reference on constant integer
using kref_int = const int &;

// Vector of integers
using vec_double = std::vector<double>;

// Returns intersection points of 2 functions (y = ax^2 + bx + c and y = dx + k)
vec_double intersection(kref_int __a, kref_int __b, kref_int __c, kref_int __d, kref_int __k)
{
    // x and y coordinates
    vec_double x_y{};

    // Copy of '__a' variable
    double new_a = static_cast<double>(__a);

    // New b variable (new_b = __b - __d)
    double new_b = static_cast<double>(__b - __d);

    // New c variable (new_c = __c - __k)
    double new_c = static_cast<double>(__c - __k);

    // Expression - formula for x1
    double x_1 = (((-1) * new_b - sqrt(pow(new_b, 2.0) - 4.0 * new_a * new_c)) / (2.0 * new_a));

    // Expression - formula for x2
    double x_2 = (((-1) * new_b + sqrt(pow(new_b, 2.0) - 4.0 * new_a * new_c)) / (2.0 * new_a));

    // Evaluation of y1
    double y_1 = static_cast<double>(__d) * x_1 + static_cast<double>(__k);

    // Evaluation of y2
    double y_2 = static_cast<double>(__d) * x_2 + static_cast<double>(__k);

    // If x1 = x2 and y1 = y2 it is no need to adding 2 pair of same elements
    if (x_1 == x_2 && y_1 == y_2)
    {
        // Adding x coordinate
        x_y.push_back(x_1);

        // Adding y coordinate
        x_y.push_back(y_1);
    }
    // Otherwise: adding all coordinates
    else
    {
        // Adding x1 coordinate
        x_y.push_back(x_1);

        // Adding y1 coordinate
        x_y.push_back(y_1);

        // Adding x2 coordinate
        x_y.push_back(x_2);

        // Adding y2 coordinate
        x_y.push_back(y_2);
    }

    // Returning x and y coordinates
    return x_y;
}

// Prints vector of x and y coordinates
void print_x_y_vec(const vec_double &__xy)
{
    std::cout << "\nxy coordinates:\n";
    std::cout << "x\ty\n";
    std::cout << "---------";

    for (size_t i = 0UL; i < __xy.size(); i++)
    {
        // If x and y coordinates are printed -> move to a new line
        if (i % 2 == 0)
            std::cout << '\n';
        
        // Printing x and y coordinates with tabulation
        std::cout << __xy[i] << '\t';
    }

    // Flushing output buffer
    std::cout << std::endl;
}

int main()
{
    std::cout << "y = ax^2 + bx + c - 1st equation. Enter ratio a, b, c.\n";
    int a{input("Enter a: ")}, b{input("Enter b: ")}, c{input("Enter c: ")};
    std::cout << "y = dx + k - 2nd equation. Enter d, k.\n";
    int d{input("Enter d: ")}, k{input("Enter k: ")};

    vec_double x_y{intersection(a, b, c, d, k)};
    print_x_y_vec(x_y);

    return EXIT_SUCCESS;
}
