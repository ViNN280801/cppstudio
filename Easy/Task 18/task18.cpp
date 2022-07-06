// Task: Write a program to convert decimal to hexadecimal.

#include <iostream>
#include <iomanip>

// Returns hexadecimal value converted from integer
const char *int_to_hex(const int &__value)
{
    // String stream
    std::stringstream ss{};

    // Converting '__value' to hexadecimal and putting it into a stringstream
    ss << "0x" << std::hex << __value;

    // String that contains result of conversion
    std::string result(ss.str());

    // Retuning result as C-style string (const char *)
    return result.c_str();
}

int main()
{
    // User's integer number
    int value{};

    std::cout << "Enter integer number to convert it into a hexadecimal: ";
    std::cin >> value;

    std::cout << "Result of conversion: " << int_to_hex(value) << std::endl;

    return EXIT_SUCCESS;
}
