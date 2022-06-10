#include <iostream>
#include <cerrno>

bool comparisonFunc(int num1, int num2, int num3){
    if(num1 == num2 || num1 == num3 || num2 == num3 || num1 == num2 == num3){
        num1 += 5;
        num2 += 5;
        num3 += 5;

        std::cout << "Transformed numbers: " << std::endl;
        std::cout << "1st number = " << num1 << std::endl;
        std::cout << "2nd number = " << num2 << std::endl;
        std::cout << "3rd number = " << num3 << std::endl;

        return true;
    }
    else if(num1 != num2 || num1 != num3 || num2 != num3){
        std::cout << "There are no equal numbers among " << num1 << ", " 
            << num2 << " and " << num3 << std::endl;        

        return false;
    }
    else{
        perror("Unknown error was occured.");
        exit(EXIT_FAILURE);
    }

    return false;
}

int main(){
    int num1 = 0, num2 = 0, num3 = 0;

    std::cout << "Enter 1st number: ";
    std::cin >> num1;
    std::cout << "Enter 2nd number: ";
    std::cin >> num2;
    std::cout << "Enter 3rd number: ";
    std::cin >> num3;

    comparisonFunc(num1, num2, num3);

    return EXIT_SUCCESS;
}