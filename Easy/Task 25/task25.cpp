// Task: Using the while loop, develop a program that will calculate the sum of numbers
// completely divisible by 5. Set the cycle from 0 to the number entered from the keyboard.

// Compile: gcc task25.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>
#include <string>

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

// Returns user's input value as 'size_t'
size_t users_input(const char *msg)
{
    // User's input string
    std::string input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> input;

        // If 'matrix_size' variable is numeric -> break loop
        if (is_number(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not a number value. Try again. \n";
    }

    // Returning converted user's inputted value to 'size_t' type
    return std::stoul(input);
}

// Returns sum of numbers which can be divided on '__div' variable
size_t sum_of_divs(const size_t &__upper, const size_t &__div)
{
    // Stores sum
    size_t sum{};

    for (size_t i = 0UL; i <= __upper; i++)
    {
        // If 'i' can be divided on a '__div' without a remainder
        if (i % __div == 0)
            // Adding to 'sum' that number
            sum += i;
    }

    // Returning sum of numbers which can be divided on '__div' number
    return sum;
}

int main()
{
    // Upper interval
    size_t upper_interval{users_input("Enter upper interval: ")};

    // The number by which it is divided
    size_t div{users_input("Enter number by which it is divided: ")};

    std::cout << "Sum of numbers which are divided on " << div \
    << " is " << sum_of_divs(upper_interval, div) << std::endl;

    return EXIT_SUCCESS;
}
