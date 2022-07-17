// Task: Create a program that will generate random numbers in the interval [a;b]
// and fill a two-dimensional array of 10 by 10 with them. In the array, you need
// to find the row number with the minimum element. Swap the array rows, the row
// with the minimum element, and the first row of the array. Organize convenient
// output to the screen.

// Compile: gcc task9.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>

// Alias for two dimensional array of dobules
using matrix_double = std::vector<std::vector<double>>;

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

// Returns true if string is a floating number (float, double, etc.)
bool is_floating_number(const std::string &__str)
{
    // Iterator for '__str' variable
    std::string::const_iterator it = __str.begin();

    // Count of points in string (must be 1 point in number)
    // Same thing with minus sign
    unsigned int count_point{0U}, count_minus{0U};

    // Iterating by symbols in string
    while (it != __str.end())
    {
        // Counting all minuses in string
        if ((*it == '-'))
            count_minus++;

        // Counting all points in string
        if ((*it == '.'))
            count_point++;

        // Incrementing iterator
        ++it;
    }

    // Exception case when point stay in the beginning of string
    if (__str.at(0UL) == '.')
        return false;

    // Moving iterator to the begin of string
    it = __str.begin();

    // If number contains less or 1 point or minus -> continue
    if (count_point <= 1U && count_minus <= 1U)
    {
        // Using 'while' loop to check if all symbols in string are digits
        while (it != __str.end() && (std::isdigit(*it) || (*it) == '.' || (*it) == '-'))
        {
            // Incrementing iterator
            ++it;
        }
    }

    return ((!__str.empty()) && (it == __str.end()));
}

// Returns user's input as floating number
template <typename T>
T input_to_floating(const char *msg)
{
    // User's input string
    std::string users_input{};

    // Using 'while' loop and string input to avoid errors
    while (true)
    {
        std::cout << msg;
        std::cin >> users_input;

        // If 'input' is contains only of digits -> break infinity loop
        if (is_floating_number(users_input))
            break;
        // Else: print message and back to the begininng of 'while' loop
        else
            std::cout << "You entered not an floating number. Try again.\n";
    }

    // Converting user's string to numeric type to return it as a result
    T num{str_to_num<T>(users_input)};

    // Returning converted user's inputted value to 'T' type
    return num;
}

// Returns true if first number bigger than the second number
template <typename T>
bool is_bigger(const T &__num1, const T &__num2)
{
    return (__num1 > __num2) ? true : false;
}

// Returns one random double number
double create_random_double(const double &__lower = 0.0, const double &__upper = 10.0)
{
    return __lower + (static_cast<double>(rand()) / RAND_MAX) * (__upper - __lower);
}

// Filling matrix of doubles with random numbers
void fill_random(matrix_double &__matrix, const double &__lower, const double &__upper)
{
    // Iterating by rows in matrix
    // '__matrix.size()' is rows
    for (size_t row{0UL}; row < __matrix.size(); row++)
    {
        // Iterating by columns in matrix
        // '__matrix.at(0).size()' is columns
        for (size_t col{0UL}; col < __matrix.at(0UL).size(); col++)
        {
            // Filling cell of matrix with random double number
            __matrix.at(row).at(col) = create_random_double(__lower, __upper);
        }
    }
}

// Printing matrix to terminal
void print_matrix(const matrix_double &__matrix)
{
    // Iterating by rows in matrix
    // '__matrix.size()' is rows
    for (size_t row{0UL}; row < __matrix.size(); row++)
    {
        // Iterating by columns in matrix
        // '__matrix[0].size()' is columns
        for (size_t col{0UL}; col < __matrix.at(0UL).size(); col++)
        {
            // Printing cell of matrix
            // All numbers will have 3 signs after point
            // If digit is 0 -> it doesn't show
            std::cout << std::setprecision(4) << __matrix.at(row).at(col) << '\t';
        }
        // Move to new line
        std::cout << '\n';
    }
    // Flushing buffer
    std::cout.flush();
}

// Returns min element in two dimensional array
double find_min(const matrix_double &__matrix)
{
    // Minimal element in matrix
    double min{__matrix.at(0UL).at(0UL)};

    // Iterating by rows in matrix
    // '__matrix.size()' is rows
    for (size_t row{0UL}; row < __matrix.size(); row++)
    {
        // Iterating by columns in matrix
        // '__matrix[0].size()' is columns
        for (size_t col{0UL}; col < __matrix.at(0UL).size(); col++)
        {
            // If we find element which is lower than previous
            // Equating it to 'min' variable
            if (min > __matrix.at(row).at(col))
                min = __matrix.at(row).at(col);
        }
    }

    // Returning minimal element from matrix
    return min;
}

// Returns indeces of min element in two dimensional array
std::pair<size_t, size_t> find_indeces_of_min(const matrix_double &__matrix)
{
    // Minimal element in matrix
    double min{__matrix.at(0UL).at(0UL)};

    size_t row_min{0UL}, col_min{0UL};

    // Iterating by rows in matrix
    // '__matrix.size()' is rows
    for (size_t row{0UL}; row < __matrix.size(); row++)
    {
        // Iterating by columns in matrix
        // '__matrix[0].size()' is columns
        for (size_t col{0UL}; col < __matrix.at(0UL).size(); col++)
        {
            // If we find element which is lower than previous
            // Equating it to 'min' variable
            if (min > __matrix.at(row).at(col))
            {
                min = __matrix.at(row).at(col);

                row_min = row;
                col_min = col;
            }
        }
    }

    // Indeces of minimal element
    std::pair<size_t, size_t> indeces_of_min{row_min + 1UL, col_min + 1UL};

    // Returning minimal element from matrix
    return indeces_of_min;
}

// Replacing row with minimal element to first row
void replace_min_to_first_row(matrix_double &__matrix)
{
    // Copy of original matrix
    matrix_double matrix_copy{__matrix};

    size_t min_row{find_indeces_of_min(__matrix).first - 1UL};

    // Iterating by columns in matrix
    // '__matrix[0].size()' is columns
    for (size_t col{0UL}; col < __matrix.at(0UL).size(); col++)
    {
        __matrix.at(0UL).at(col) = __matrix.at(min_row).at(col);
    }

    // Iterating by columns in matrix
    // '__matrix[0].size()' is columns
    for (size_t col{0UL}; col < __matrix.at(0UL).size(); col++)
    {
        __matrix.at(min_row).at(col) = matrix_copy.at(0UL).at(col);
    }
}

int main()
{
    srand(time(nullptr));

    // Count of rows and columns of two dimensional array
    size_t rows{input_to_uint<size_t>("Enter count of rows: ")},
        cols{input_to_uint<size_t>("Enter count of columns: ")};

    // Lower and upper intervals for generate numbers within these limits
    double lower_interval{0.0}, upper_interval{0.0};

    // Using infinity cycle to avoid this case:
    // 'upper_interval' < 'lower_interval'
    while (true)
    {
        lower_interval = input_to_floating<double>("Enter lower interval: ");
        upper_interval = input_to_floating<double>("Enter upper interval: ");

        // If upper interval is bigger than the lower interval -> break the cycle
        if (is_bigger<double>(upper_interval, lower_interval))
            break;
        else
            std::cout << upper_interval << " < or = " << lower_interval << ". Try again:\n";
    }

    // Initializing two dimensional vector of doubles filled with 0
    matrix_double matrix(rows, std::vector<double>(cols, 0));

    fill_random(matrix, lower_interval, upper_interval);
    print_matrix(matrix);

    std::cout << "\nMinimal element is " << find_min(matrix) << std::endl;
    std::cout << "Indeces of minimal element are: [" << find_indeces_of_min(matrix).first
              << ", " << find_indeces_of_min(matrix).second << ']' << std::endl;

    std::cout << "\nMatrix with replaced rows: " << std::endl;
    replace_min_to_first_row(matrix);
    print_matrix(matrix);

    return EXIT_SUCCESS;
}
