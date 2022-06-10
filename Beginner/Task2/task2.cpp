#include <iostream>

int main(){
    int a = 0, b = 0, f = 0;

    std::cout << "Enter number \"a\": ";
    std::cin >> a;
    std::cout << "Enter number \"b\": ";
    std::cin >> b;
    std::cout << "Enter number \"f\": ";
    std::cin >> f;

    if(a == 0){
        std::cout << "\"a\" can't be a 0, because \"f\" is dividing to \"a\"" << std::endl;
        
        exit(EXIT_FAILURE);
    }

    std::cout << "Result of math expression is " << (a + b - f / a) + f * a * a - (a + b)
     << std::endl;

    return EXIT_SUCCESS;
}