// Task: Using the do while loop operator, create
// a program that will require entering numbers from the keyboard until the digit 1 is entered.

#include <iostream>
#include <vector>
#include <string>

// Returns true if '__str' is digit
// Otherwise: returns false
bool is_string_digit(const std::string &__str)
{
    return (__str.size() == 1UL && isdigit(__str[0])) ? true : false;
}

// Returns vector of entered by user numbers
std::vector<int> get_nums()
{
    // User's digits
    std::vector<int> nums{};

    // User's input string
    std::string input{};

    // Digit (converted number from user's input string)
    int digit{0};

    std::cout << "Enter digits (enter \'1\' to exit): " << std::endl;

    do
    {
        // Skipping all whitespaces
        std::cin >> std::skipws;

        std::cin >> input;

        if (is_string_digit(input))
        {
            digit = std::stoi(input);
            nums.push_back(digit);
        }
        else
            std::cout << "Incorrect input.\n";

    } while (digit != 1);

    return nums;
}

// Prints vector of integer numbers
void print_nums(const std::vector<int> &__nums)
{
    for (size_t index = 0UL; index < __nums.size(); index++)
    {
        std::cout << __nums[index] << '\t';
    }

    // Flushing buffer
    std::cout << std::endl;
}

int main()
{
    // Stores user's numbers
    std::vector<int> nums{get_nums()};

    std::cout << "Entered numbers: " << std::endl;

    // Printing vector of numbers
    print_nums(nums);

    return EXIT_SUCCESS;
}
