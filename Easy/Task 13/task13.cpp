#include <iostream>
#include <list>
#include <algorithm>

// Returns array of integer values that contain all digits from number
std::list<int> split_on_digits(const int &__number)
{
    // Initializing list of digits to return it as a result
    std::list<int> digits{};

    // Initializing copy of '__number'
    int number_copy{__number};

    while (number_copy > 0)
    {
        // Take last digit from number
        int digit{number_copy % 10};

        // Changing number by dividing
        number_copy /= 10;

        // Pushing front digit into a list
        // reversing digits because we took them in reversed order
        // so, we need to reverse them again
        digits.push_front(digit);
    }

    // Returning list of digits
    return digits;
}

// Returns 'true' if number contains same digits,
// 'false' - otherwise
bool same_digits_in_number(const int &__number)
{
    // Initializing boolean flag to return result
    bool flag{false};

    // Initializing list of digits to return it as a result
    std::list<int> digits{split_on_digits(__number)};

    // Initializing iterator on a begin of list to iterate by elements
    std::list<int>::iterator it{digits.begin()};

    // Using 'while' loop and STL algorithm 'adjacent_find()' to check same digits
    while((it = std::adjacent_find(it, digits.end())) != digits.end())
    {
        // Assigning 'true' value to a flag
        flag = true;

        // Breaking cycle if flag is true
        break;

        // Incrementing iterator
        ++it;
    }

    // Returning result of search
    return flag;
}

int main()
{
    // Checking same digits
    std::cout << same_digits_in_number(334) << std::endl;
    std::cout << same_digits_in_number(123456789) << std::endl;
    std::cout << same_digits_in_number(61837) << std::endl;
    std::cout << same_digits_in_number(124421) << std::endl;

    return EXIT_SUCCESS;
}