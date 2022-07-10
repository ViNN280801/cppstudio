// Task: The program checks whether the number entered from the keyboard is an integer.

// Compile: gcc task29.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>
#include <string>
#include <cassert>

// Returns true if string is a number
bool is_number(const std::string &__str)
{
    std::cout << __str << std::endl;

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
        {
            std::cout << "Entered number is integer number.\n";
            break;
        }
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an integer number. Try again.\n";
    }

    // Returning converted user's inputted value to 'int' type
    return std::stoi(input);
}

int main()
{
    [[maybe_unused]]int in{input("Enter number: ")};

    return EXIT_SUCCESS;
}