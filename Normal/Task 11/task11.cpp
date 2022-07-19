// Task: Given an array of size "n", fill it with random numbers, find all the odd numbers of the array.

// Compile: gcc task11.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>
#include <sstream>
#include <vector>

// Alias for unsigned integer numbers
using uint = unsigned int;

// Returns numeric type from a string '__str'
template <typename T>
T str_to_num(const std::string &__str)
{
    // Input string stream
    std::istringstream iss(__str);

    // Numeric variable to return
    T num{};

    // Writing string to numeric type from a string stream
    iss >> num;

    // Returning result number
    return num;
}

// Returns true if string is a unsigned integer number (unsigned short, unsigned int, size_t, etc.)
bool is_uint_number(const std::string &__str)
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

// Returns user's input as unsigned integer number
template <typename T>
T input_to_uint(const char *msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_uint_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an unsigned integer number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_num<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

// Fills empty vector with random unsigned integer numbers
void fill_arr_random_uint(std::vector<uint> &__arr, const size_t &__arrsize)
{
    // Iterating by elements in array
    for (size_t index{0UL}; index < __arrsize; index++)
    {
        // Creating and filling array with random unsigned integer numbers
        __arr.push_back(rand() % 100U + 1U);
    }
}

// Prints array to terminal
void print_arr_uint(const std::vector<uint> &__arr)
{
    // Iterating by elements in array
    for (size_t index{0UL}; index < __arr.size(); index++)
    {
        std::cout << __arr.at(index) << '\t';
    }

    // Flushing output buffer
    std::cout << std::endl;
}

// Prints odd unsigned integer numbers to terminal
void print_odd(const std::vector<uint> &__arr)
{
    // Iterating by elements in array
    for (size_t index{0UL}; index < __arr.size(); index++)
    {
        if (__arr.at(index) % 2 != 0)
            std::cout << __arr.at(index) << '\t';
    }

    // Flushing output buffer
    std::cout << std::endl;
}

int main()
{
    // The pseudo-random number generator
    srand(time(nullptr));

    // Size of array which is entered by user
    size_t arr_size{input_to_uint<size_t>("Enter size of array: ")};

    // Array
    std::vector<uint> arr{};

    // Filling array with random unsigned integer numbers
    fill_arr_random_uint(arr, arr_size);

    // Printing this array
    std::cout << "Array:\n";
    print_arr_uint(arr);

    // Printing odd numbers
    std::cout << "Odd numbers:\n";
    print_odd(arr);

    return EXIT_SUCCESS;
}