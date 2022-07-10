// Task: Using the for loop operator, develop a program that will
// output the multiplication table of the number entered by the user from the keyboard.

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

        // If 'matrix_size' variable is numeric -> break loop
        if (is_number(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not a number value. Try again. \n";
    }

    // Returning converted user's inputted value to 'size_t' type
    return std::stoi(input);
}

// Prints multiplication table for '__num' number
void multiplication_table(const int &__num)
{
    // Using 'for' loop to print multiplication table for '__num' number
    for (int i = 1; i <= 10; i++)
    {
        std::cout << i << " * " << __num << " = " << i * __num << '\n';
    }

    // Flushing output buffer 
    std::cout << std::endl;
}

int main()
{
    int number{input("Enter the number: ")};
    multiplication_table(number);

    return EXIT_SUCCESS;
}