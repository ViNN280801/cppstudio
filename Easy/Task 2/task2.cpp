#include <iostream>
#include <cmath>

int main(){
    int N = 0, k = 0, sum = 0;

    std::cout << "Enter N: ";
    std::cin >> N;

    if(N <= 0){
        std::cout << "N can't be <= 0" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(N > 0){
        std::cout << "Enter degree k: ";
        std::cin >> k;

        while(N >= 1){
            sum += (int)pow(N, k);
            N--;
        }

        std::cout << "Result of sum is " << sum << std::endl;
    }
    else{
        std::cout << "Unknown error was occured." << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}