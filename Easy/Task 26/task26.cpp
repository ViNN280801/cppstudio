// Task: The program should output a table of squares of numbers from 1 to 5
// (it is necessary to use tabulation and newline, see control characters).
// In the first column there should be numbers from 1 to 5 in the second
// column there should be squares of these numbers

#include <iostream>
#include <iomanip>
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
int users_input(const char *msg)
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

// Prints table of squares from 1 to '__last'
void square_tables(const int &__last)
{
    std::cout << std::setw(5) << ' ' << "Square tables " << std::endl;
    
    for (int i = 1; i <= __last; i++)
    {
        std::cout << i << std::setw(20) << std::setfill(' ') << i * i << '\n';
    }
    std::cout << std::endl;
}

int main()
{
    int last{users_input("Enter last number: ")};
    square_tables(last);

    return EXIT_SUCCESS;
}
