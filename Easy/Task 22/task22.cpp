// Task: Find the trace of the matrix, the trace of the
// matrix is the sum of the elements of the main diagonal.
// The size of the matrix is entered by the user, the matrix is filled with random numbers.

// Compile: gcc task22.cpp -o main -lstdc++ -std=c++20 -Wall -Wextra -Wpedantic

#include <iostream>
#include <string>
#include <vector>
#include <concepts>

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

// Alias to short the record vector<vector<int>>
template <typename T>
using matrix_t = std::vector<std::vector<T>>;

// Prints matrix to terminal
template <typename T>
void print_matrix(const matrix_t<T> &__mt)
{
    // Iterating by rows
    for (size_t row = 0UL; row < __mt.size(); row++)
    {
        // Iterating by columns
        for (size_t col = 0UL; col < __mt.size(); col++)
        {
            // Printing element to terminal
            std::cout << __mt[row][col] << '\t';
        }
        std::cout << '\n';
    }
    // Flushing output stream
    std::cout.flush();
}

// Returns NxN matrix with randomly filled integer numbers
template <typename T>
matrix_t<T> fill_matrix_randomly(const size_t &__size)
{
    srand(time(nullptr));

    // Matrix of integer numbers
    matrix_t<int> matrix(__size, std::vector(__size, 0));

    // Iterating by rows
    for (size_t row = 0UL; row < __size; row++)
    {
        // Iterating by columns
        for (size_t col = 0UL; col < __size; col++)
        {
            // Generating number from 1 to 100
            // Assigning it to an matrix
            matrix[row][col] = rand() % 100 + 1;
        }
    }

    // Returning filled matrix
    return matrix;
}

// Declaring typename C
template <typename C>
// This concept tells us that typename C have to be summable
// Means that we can get sum of this type
concept summable = requires(C x, C y)
{
    x + y;
};

// Returns sum of diagonal elements of matrix
template <typename C>
C diagonal_sum(matrix_t<C> __mt)
{
    // Sum of diagonal elements in matrix
    C sum{};

    // Iterating by rows
    for (size_t row = 0UL; row < __mt.size(); row++)
    {
        // Iterating by columns
        for (size_t col = 0UL; col < __mt.size(); col++)
        {
            // If indeces of element are same -> do +=
            if (row == col)
                sum += __mt[row][col];
        }
    }

    // Returning result of sum
    return sum;
}

int main()
{
    // Stores size of future matrix in string represenatation
    std::string matrix_size{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << "Enter size of matrix: ";
        std::cin >> matrix_size;

        // If 'matrix_size' variable is numeric -> break loop
        if (is_number(matrix_size))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not a number value. Try again. \n";
    }

    // Stores size of matrix in unsigned long integer representation
    size_t size = std::stoul(matrix_size);

    // Filling matrix variable with random integer numbers
    matrix_t<int> matrix{fill_matrix_randomly<int>(size)};

    // Printing matrix to terminal
    print_matrix(matrix);

    // Printing result of sum
    std::cout << "Sum of diagonal elements: " << diagonal_sum(matrix) << std::endl;

    return EXIT_SUCCESS;
}
