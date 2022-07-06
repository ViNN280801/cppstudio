#include <iostream>

// Returns choice of user as a character
char do_choice()
{
    // Initializing empty char to store choice of user
    unsigned short int choice{};

    std::cout << "Enter number with a symbol: \n1. \'*\'\n2. \'+\'\n3. \'#\'\n";
    std::cin >> choice;

    // Using 'switch' operator to return certain symbols
    switch (choice)
    {
    case 1:
        return '*';
    case 2:
        return '+';
    case 3:
        return '#';
    default:
        std::cout << "There is no such symbol. By default \'*\' selected. " << std::endl;
        break;
    }

    // Returning '*' by default
    return '*';
}

// Prints rhombus with '__symbol'
// Gets symbol which will be printed
void print_rhombus(const char &__symbol)
{
    // Initializing height, width of rhombus
    // and current position
    int side_length{}, pos{};

    std::cout << "Enter length of the large diagonal of the rhombus: ";
    std::cin >> side_length;

    // Using double 'for' loop to plot the rhombus
    for (int y_coordinate = 1; y_coordinate <= side_length; y_coordinate++)
    {
        for (int x_coordinate = 1; x_coordinate <= side_length; x_coordinate++)
        {
            if ((x_coordinate == ((side_length / 2) + 1 + pos)) || (x_coordinate == ((side_length / 2) + 1 - pos)))
                std::cout << __symbol;
            else
                std::cout << ' ';
        }
        std::cout << '\n';

        if (y_coordinate < (side_length / 2) + 1)
            pos++;
        else
            pos--;
    }
}

int main()
{
    // Initializing symbol with user input
    char choice{do_choice()};

    // Printing rhombus
    print_rhombus(choice);

    return EXIT_SUCCESS;
}
