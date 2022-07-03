#include <iostream>

// Initializing static variable to store next value
static int next = 7;

// Returns pseudo generated number by linear congruental method
// If error occured -> returns -1;
double generate_pseudo_nums(const int &__multiplier = 7, const int &__increment = 7,
                            const int &__mod = 10)
{
    // Checking intervals of variables
    if (((__multiplier >= 0.0) && (__multiplier < __mod)) &&
        ((__increment >= 0.0) && (__increment < __mod)) &&
        (next >= 0.0) && (next < __mod) &&
        __mod >= 2.0)
    {
        // Calculating next value
        next = (__multiplier * next + __increment) % __mod;

        // Returning result
        return static_cast<double>(next);
    }
    // If intervals are invalid -> return -1;
    else
        return -1.0;
}

int main()
{
    for(int i = 0; i < 15; i++)
    {
        std::cout << generate_pseudo_nums(8, 65, 100) << std::endl;
    }

    return EXIT_SUCCESS;
}