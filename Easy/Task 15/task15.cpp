#include <iostream>

// Initializing constan strings with messages
const char *brick_passed{"The brick passes through the hole"};
const char *brick_not_passed{"The brick does not pass through the hole"};

// Returns string as a result of passing brick into a hole
const char *is_brick_pass(const double &__brick_length = 1, const double &__brick_width = 1, const double &__brick_height = 1,
                          const double &__opening_length = 1, const double &__opening_heigth = 1)
{
    // Checking if the brick can pass through the hole
    if ((__brick_width < __opening_heigth && __brick_length < __opening_length) ||
        (__brick_length < __opening_length && __brick_width < __opening_heigth) ||
        (__brick_width < __opening_length && __brick_height < __opening_heigth))
        return brick_passed;
    // Otherwise:
    else
        return brick_not_passed;
}

int main()
{
    // Initializing sizes of brick and size of a hole
    double brick_length{}, brick_width{}, brick_height{}, hole_length{}, hole_height{};

    std::cout << "Enter length of a brick: ";
    std::cin >> brick_length;
    std::cout << "Enter width of a brick: ";
    std::cin >> brick_width;
    std::cout << "Enter height of a brick: ";
    std::cin >> brick_height;

    std::cout << "Enter length of a hole: ";
    std::cin >> hole_length;
    std::cout << "Enter height of a hole: ";
    std::cin >> hole_height;

    // Output result in a terminal
    std::cout << is_brick_pass(brick_length, brick_width, brick_height, hole_length, hole_height) << std::endl;

    return EXIT_SUCCESS;
}