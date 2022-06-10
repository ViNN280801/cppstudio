#include <iostream>

void printFunc()
{
    printf("\n");

    static const char *const text[5][8] =
        {
            {"FFFF", "U  U", "CCCC", "K  K", "    ", "Y  Y", "OOOO", "U  U"},
            {"F   ", "U  U", "C   ", "K K ", "    ", "Y  Y", "O  O", "U  U"},
            {"FFFF", "U  U", "C   ", "K   ", "    ", " YY ", "O  O", "U  U"},
            {"F   ", "U  U", "C   ", "K K ", "    ", " YY ", "O  O", "U  U"},
            {"F   ", "UUUU", "CCCC", "K  K", "    ", " YY ", "OOOO", "UUUU"},
        };

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            std::cout << text[i][j] << "\t";
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    printFunc();
    std::cout << "t   House:nn";
    std::cout << "t     / \n";
    std::cout << "t    /   \n";
    std::cout << "t   /     \n";
    std::cout << "t  /------ \n";
    std::cout << "t / |    |  \n";
    std::cout << "t   |    | \n";
    std::cout << "t   |    | \n";
    std::cout << "t   |____| \n";

    return EXIT_SUCCESS;
}