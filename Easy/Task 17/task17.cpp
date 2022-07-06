// Task: Create a program that should receive a sequence of
// digits at the input, after which the program shows the digit
// whose serial number was entered by the user.

#include <iostream>
#include <string>

// Returns true if all symbols in string are digits
bool is_digits_in_string(const std::string &__str)
{
    // Boolean variable to store result
    bool flag{};

    // Using 'for' loop to iterate in string by all symbols
    for (size_t index = 0UL; index < __str.length(); index++)
    {
        // If symbol is digit, assigning 'true' to 'flag'
        if (isdigit(__str[index]))
            flag = true;
        // Otherwise: assigning 'false' to 'flag'
        // and breaking the cycle
        else
        {
            flag = false;
            break;
        }
    }

    // Returning result
    return flag;
}

// Returns k-th digit in string of numbers (all numbers are positive)
// Returns -1 if something wrong (symbols are not numbers or numbers are negative, or smth else)
// Gets string and position in string as parameters
int get_digit_from_string(const std::string __str, const size_t &__pos)
{
    // Variable to store necessary digit
    int digit{};

    // Check if all sybmols in string are digits
    if (is_digits_in_string(__str))
    {
        // Using 'for' loop to iterate by symbols in string
        for (size_t index = 0UL; index < __str.length(); index++)
        {
            // If we met necessary position of symbol in string -> remember this digit and break the cycle
            if (__pos == index)
            {
                // Converting character to integer value and assigning this value to 'digit' variable
                digit = __str[index] - '0';
                break;
            }
        }
    }
    else
        return -1;

    // Returning result
    return digit;
}

int main()
{
    // String for user input
    std::string user_str{};

    // Position of necessary digit in string
    size_t pos{};

    std::cout << "Enter the string: ";
    std::cin >> user_str;
    std::cout << "Enter position of certain digit: ";
    std::cin >> pos;

    std::cout << "Result of search: " << get_digit_from_string(user_str, pos) << std::endl;

    return EXIT_SUCCESS;
}
