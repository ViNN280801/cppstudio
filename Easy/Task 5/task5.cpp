#include <iostream>

int exponentationFunc(int number, int degree){
    int result = 1;

    for(int i = 0; i < degree; i++){
        result *= number;
    }

    return result;
}

int main(){
    int number = 0, degree = 0;

    std::cout << "Enter number: ";
    std::cin >> number;
    std::cout << "Enter degree: ";
    std::cin >> degree;

    std::cout << number << "^" << degree << " = " << exponentationFunc(number, degree) << std::endl;
    
    return EXIT_SUCCESS;
}