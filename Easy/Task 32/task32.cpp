// Task: It is required to output from the 1st to 6 isosceles triangles
// to the console, depending on what number the user enters. For example, if
// the number 3 is sent to the program, then 3 triangles must be printed, if
// the user enters 6, then 6 triangles must be printed. Triangles should be displayed
// not in a column, but in a row. The size of the triangles is also formed by the
// number entered by the user. As I said, if the user enters the number 3,
// then three isosceles triangles should be printed, the height of which is — 3 m.
// To print triangles, you can choose any symbol as you like, the existing solution
// uses the asterisk symbol — *.

// Compile: gcc task32.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>

// Returns true if '__str' is digit
// Otherwise: returns false
bool is_character(const std::string &__str)
{
    return (__str.size() == 1UL && !isdigit(__str[0])) ? true : false;
}

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
unsigned int input_to_uint(const char *msg)
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

// Returns user's input value as 'unsigned int'
char input_to_ch(const char *msg)
{
    // User's input string
    std::string input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> input;

        // If 'input' is contains only 1 character -> break infinity loop
        if (is_character(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an character. Try again.\n";
    }

    // Returning converted user's inputted character
    return input[0];
}

// Prints '__count' isosceles triangles with height = '__count' and with symbol = '__ch'
void print_triangles(const unsigned int &__count, const char &__ch)
{
    // Length of line
    unsigned int length{((__count * 2U) - 1U)};

    for (unsigned int i{0U}; i < __count; i++)
    {
        for (unsigned int j{0U}; j < __count; j++)
        {
            for (unsigned int k(0U); k <= length; k++)
            {
                if ((k == __count - i) || (k == __count) || (k == __count + i))
                {
                    std::cout << __ch;
                    while (k < (__count + i))
                    {
                        std::cout << __ch;
                        k++;
                    }
                }
                else
                    std::cout << ' ';
            }
        }
        std::cout << '\n';
    }

    // Flushing output buffer
    std::cout.flush();
}

int main()
{
    unsigned int count{input_to_uint("Enter count of isosceles triangles: ")};
    char symbol{input_to_ch("Enter symbol which will be printed isosceles triangles: ")};

    print_triangles(count, symbol);

    return EXIT_SUCCESS;
}
