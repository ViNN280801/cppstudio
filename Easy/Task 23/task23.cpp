// Task: Develop a function to which an array of float type and its size are passed as arguments.
// The function should return the arithmetic mean of the array elements.

#include <iostream>
#include <concepts>
#include <vector>
#include <string>

// Declaring 'T' typename
template <typename T>
// Suggests that the simplest mathematical operations can be performed on all variables of type T
concept type_math_operations = requires(T x, T y)
{
    x + y;
    y + x;
    x - y;
    y - x;
    x * y;
    y * x;
    x / y;
    y / x;
};

// Vector of T types
template <typename T>
using vec_t = std::vector<T>;

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

// Prints array element by element with tabulation to terminal
template<typename T>
void print_arr(const vec_t<T> &__arr)
{
    for (size_t index = 0Ul; index < __arr.size(); index++)
    {
        std::cout << __arr[index] << '\t';
    }
    std::cout << std::endl;
}

// Fills vector with random values
template<typename T>
void fill_arr_randomly(vec_t<T> &__arr, const size_t &__size)
{
    srand(time(nullptr));

    for (size_t index = 0UL; index < __size; index++)
    {
        // Filling randomly with different values from 1 to 100
        __arr[index] = rand() % 100 + 1;
    }
}

// Returns arithmetic mean from array
template <typename T>
T avg_arr(const vec_t<T> &__arr)
{
    // Average of array
    T avg{};

    for (size_t index = 0UL; index < __arr.size(); index++)
    {
        // Sum of all elements
        avg += __arr[index];
    }

    // Returning avarage of array
    return avg / __arr.size();
}

int main()
{
    // User's input string
    std::string input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << "Enter size of array: ";
        std::cin >> input;

        // If 'matrix_size' variable is numeric -> break loop
        if (is_number(input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not a number value. Try again. \n";
    }

    // Array size (converted from string array size representation)
    size_t arr_size{std::stoul(input)};

    // Array of float
    vec_t<float> float_arr(arr_size);

    // Filling array with random values
    fill_arr_randomly(float_arr, arr_size);

    // Printing array to terminal
    print_arr(float_arr);

    std::cout << "Average of array: " << avg_arr<float>(float_arr) << std::endl;

    return EXIT_SUCCESS;
}
