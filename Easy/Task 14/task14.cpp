#include <iostream>
#include <string>

// Returns count of paragraphs in text as size_t
size_t count_of_paragraphs(const std::string &str)
{
    // Initializing counter for paragraphs
    size_t counter{};

    /* Now, we need to  count how many '\n' symbols we have in text
    So we'll count how many paragraphs we have in the text */

    // Removing all spaces using 'for' loop
    for (size_t char_index = 0UL; char_index < str.length(); char_index++)
    {
        // If current sybmol is '\n' and next symbol is character or numeric
        if (str[char_index] == '\n' && isalnum(str[char_index + 1UL]))
            counter++;
    }

    // Returning count of parahraphs
    return counter;
}

int main()
{
    // Initializing string which will be contain user's text
    std::string text;

    std::cout << "Enter text (Enter # to terminate input): " << std::endl;

    // Getting lines while until we met '#' symbol
    getline(std::cin, text, '#');

    // Output result
    std::cout << "Count of paragraphs: " << count_of_paragraphs(text) << std::endl;
}