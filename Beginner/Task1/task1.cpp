#include <iostream>

int main(){
    short int choose = 0;
    int number;

    start:

    std::cout << "Enter the 5 digit number: ";  
    std::cin >> number;
    std::cout << std::endl;

    if(number > 9999 && number <= 99999){
        std::cout << "1 digit is " << (number / 10000)  << std::endl;
        std::cout << "2 digit is " << (number / 1000) % 10 << std::endl;
        std::cout << "3 digit is " << ((number / 100) % 100) % 10 << std::endl;
        std::cout << "4 digit is " << ((number / 10) % 1000) % 100 % 10 << std::endl;
        std::cout << "5 digit is " << (number % 10) << std::endl;
    }
    else{
        std::cout << "You entered not 5 digit number." << std::endl;
        std::cout << "1. Try again." << std::endl;
        std::cout << "2. Exit from program." << std::endl;
        std::cin >> choose;

        if(choose == 1){
            goto start;
        }
        else if(choose == 2){
            exit(EXIT_SUCCESS);
        }
        else{
            std::cout << "Unknown error was occured." << std::endl;

            exit(EXIT_FAILURE);
        }

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}