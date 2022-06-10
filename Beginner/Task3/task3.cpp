#include <iostream>
#include <cctype>

int main(){
    char letter = ' ';

    std::cout << "Enter a letter: ";
    std::cin >> letter;

    letter -= 32;

    if(isalpha(letter)){
        std::cout << "Your letter in upper register is " << letter << std::endl;
    }
    else if(!isalpha(letter)){
        std::cout << "You entered not a letter." << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        std::cout << "Unknown error was occured." << std::endl;
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}