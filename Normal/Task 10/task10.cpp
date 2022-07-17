// Task: Count the number of repetitions of elements, a given set of characters, in the entered string.

// Compile: gcc task10.cpp -o main -lstdc++ -Wall -Wpedantic -Wextra

#include <iostream>
#include <unordered_map>

// Prints symbol and count of repeats
void print_repeats(const std::string &__str)
{
    // Unordered map with characters and count of repeats
    std::unordered_map<char, unsigned int> ch_and_repeats{};

    // Iterating by symols
    for (size_t index{0UL}; index < __str.length(); index++)
    {
        ch_and_repeats[__str[index]]++;
    }

    // Iterating in map
    for (auto it : ch_and_repeats)
    {
        // If we have 1 more same elements -> print character and count of repeats
        if(it.second >= 1U)
            std::cout << it.first << '\t' << it.second << '\n';
    }

    // Flusgin buffer
    std::cout.flush();
}

int main()
{
    // User's input string
    std::string users_input{};

    std::cout << "Enter string: ";

    // Input string to 'users_input' while '\n' symbol
    getline(std::cin, users_input);

    print_repeats(users_input);

    return EXIT_SUCCESS;
}