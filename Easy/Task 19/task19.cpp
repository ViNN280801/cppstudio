// Task: The program must accept five-digit numbers as input
// and determine whether the entered five-digit number is a palindrome.

#include <iostream>
#include <algorithm>

// Returns 'true' if integer number is palindrome, 'false' otherwise
bool is_palindrome(const int &__val)
{
    // String variable that stores '__val' integer number
    std::string s_val(std::to_string(__val));

    // String variable that stores 's_val'
    std::string reversed_s_val{s_val};

    // Reversing copy of 's_val'
    std::reverse(reversed_s_val.begin(), reversed_s_val.end());

    // If string = reversed string -> that means string which contains '__val' is palindrome
    if (s_val == reversed_s_val)
        return true;
    else
        return false;
}

int main()
{
    // Variable to store user's input integer number
    int number{};

    std::cout << "Enter integer value: ";

    // Using 'try-catch' operator to avoid invalid inputting
    try
    {
        std::cin >> number;

        if (is_palindrome(number))
            std::cout << "Number " << number << " is palindrome. " << std::endl;
        else
            std::cout << "Number " << number << " is not palindrome. " << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
    }

    return EXIT_SUCCESS;
}
