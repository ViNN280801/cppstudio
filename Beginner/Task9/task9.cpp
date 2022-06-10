#include <iostream>

int main(){
    int firstNumber = 0, secondNumber = 0;

    std::cout << "Enter 1st number: ";
    std::cin >> firstNumber;
    std::cout << "Enter 2nd number: ";
    std::cin >> secondNumber;

    if(firstNumber < secondNumber)
        std::cout << firstNumber << " < " << secondNumber << std::endl;
    else if(firstNumber > secondNumber)
        std::cout << firstNumber << " > " << secondNumber << std::endl;
    else if(firstNumber == secondNumber)
        std::cout << firstNumber << " = " << secondNumber << std::endl;
    else{
        std::cout << "Unknown error occurs." << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}