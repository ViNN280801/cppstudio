#include <iostream>

double calcChainFraction(int count){
    double result = 1;

    for(int i = 0; i < count; i++)
        result = 1 + 1 / result;

    return result;
}

int main(){
    int count = 0;

    std::cout << "Enter count of elements: ";
    std::cin >> count;

    std::cout << "Result of calculating chain fraction is " << calcChainFraction(count) << std::endl;    

    return EXIT_SUCCESS;
}