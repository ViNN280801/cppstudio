// Task: Using the while loop, develop a program that will calculate the
// sum of numbers completely divisible by 5. Set the cycle from 0 to the
// number entered from the keyboard.

// Compile:

#include <iostream>

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

// Returns user's input value as 'unsigned int'
unsigned int input(const char *msg)
{
    // User's input string
    std::string input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_number(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an integer number. Try again.\n";
    }

    // Returning converted user's inputted value to 'int' type
    return std::stoi(input);
}

// Constant reference on unsigned integer number
using k_uint_ref = const unsigned int &;

// Returns sum of numbers from sequence which are can be divided on '__divider'
unsigned int sum_of_sequence(k_uint_ref __last, k_uint_ref __divider)
{
    // Sum of numbers from sequence which are can be divided on '__divider'
    unsigned int sum{0U};

    // Variable for 'while' loop
    unsigned int while_var{0UL};

    while (while_var <= __last)
    {
        if ((while_var % __divider) == 0)
            sum += while_var;
        
        while_var++;
    }

    // Returning sum
    return sum;
}

int main()
{
    unsigned int last_number{input("Enter last number of sequence (must be positive integer number): ")},
        divider{input("Enter number on which other numbers from sequence will be divided on: ")};

    std::cout << "Sum of numbers from sequence which are can be divided on " << divider << " = " << sum_of_sequence(last_number, divider) << std::endl;

    return EXIT_SUCCESS;
}