// Task: The program must perform string conversions (string length 255 characters):

// STRING IN CAPITAL LETTERS
// lowercase string
// With A Capital Letter (The First Character Of Each Word In The Line)
// The First Character in Lowercase
// As in the sentence (with a capital letter).
// The 'f' symbol means exiting the program

// Organize a menu in the program through which you can conveniently
//  select any action. The program must be executed until the
//  user enters the 'f' character.

// Compile: gcc task8.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>

// Maximum count of symbols
const short int BUFFER_SIZE{255};

// Returns user's inputted string with whitespaces
std::string input(const char *__msg = "")
{
    // Printing message
    std::cout << __msg;

    // User's string
    char buffer[BUFFER_SIZE]{0};

    // Reading data from input stream with whitespaces and max size of buffer = 255
    std::cin.getline(buffer, BUFFER_SIZE);

    // User's string as 'std::string' type (converted from character array)
    std::string users_str{buffer};

    // Returning result string
    return users_str;
}

// Modifies string where all letters will be in upper case
void all_to_upper(std::string &__str)
{
    // Iterating by symbols with 'for' loop
    for (size_t index{0UL}; index < __str.size(); index++)
    {
        // Transforming each letter to upper case
        __str.at(index) = static_cast<char>(toupper(__str.at(index)));
    }
}

// Modifies string where all letters will be in lower case
void all_to_lower(std::string &__str)
{
    // Iterating by symbols with 'for' loop
    for (size_t index{0UL}; index < __str.size(); index++)
    {
        // Transforming each letter to lower case
        __str.at(index) = static_cast<char>(tolower(__str.at(index)));
    }
}

// Modifies string where all 1st letters will be in upper case
void all_first_to_upper(std::string &__str)
{
    // Transforming first letter of string to upper case
    __str.at(0UL) = static_cast<char>(toupper(__str.at(0UL)));

    // Iterating by symbols with 'for' loop
    for (size_t index{0UL}; index < __str.size(); index++)
    {
        // If symbol is whitespace -> transform next symbol to upper case
        if (__str.at(index) == ' ' && ((index + 1UL) < __str.size()) && isalpha(__str.at(index + 1UL)))
            // Transforming letter to upper case
            __str.at(index + 1UL) = static_cast<char>(toupper(__str.at(index + 1UL)));
    }
}

// Modifies string where all 1st letters will be in lower case
void all_first_to_lower(std::string &__str)
{
    // Transforming first letter of string to lower case
    __str.at(0UL) = static_cast<char>(tolower(__str.at(0UL)));

    // Iterating by symbols with 'for' loop
    for (size_t index{0UL}; index < __str.size(); index++)
    {
        // If symbol is whitespace -> transform next symbol to lower case
        if (__str.at(index) == ' ' && ((index + 1) < __str.size()) && isalpha(__str.at(index + 1UL)))
            __str.at(index + 1UL) = static_cast<char>(tolower(__str.at(index + 1UL)));
    }
}

// Modifies string where all letters will be in upper case
void capital(std::string &__str)
{
    __str.at(0UL) = static_cast<char>(toupper(__str.at(0UL)));
}

// Returns true if '__str' is character
// Otherwise: returns false
bool is_alone_symbol(const std::string &__str)
{
    return (__str.size() == 1UL) ? true : false;
}

// Prints menu and returns selected point
char print_menu()
{
    std::string selected{};

    std::cout << "1. Transform all symbols from string to upper case;\n";
    std::cout << "2. Transform all symbols from string to lower case;\n";
    std::cout << "3. Transform all first letters from string to upper case;\n";
    std::cout << "4. Transform all first letters from string to lower case, other - to upper case;\n";
    std::cout << "5. Transform 1st symbol to upper case;\n";
    std::cout << "6. Enter \'F\'/\'f\' characters to exit;\n";
    std::cout << "Enter choice: ";
    std::cin >> selected;

    if (is_alone_symbol(selected))
        // Returning selected point of menu
        return selected.at(0UL);
    else
        return 'f';
}

// Prints transformed string
void transform_str(std::string &__str, const char &__choice)
{
    switch (__choice)
    {
    case '1':
        all_to_upper(__str);
        break;
    case '2':
        all_to_lower(__str);
        break;
    case '3':
        all_first_to_upper(__str);
        break;
    case '4':
        all_first_to_lower(__str);
        break;
    case '5':
        capital(__str);
        break;
    default:
        break;
    }
}

int main()
{
    // User's inputted string
    std::string str{input("Enter string (max size - 255): ")};

    while (true)
    {
        std::cout << str << '\n';
        char selected{print_menu()};
        transform_str(str, selected);

        if (selected == 'F' || selected == 'f')
            break;

        std::cout << '\n';
    }

    // Flusing buffer
    std::cout.flush();

    return EXIT_SUCCESS;
}
