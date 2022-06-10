#include <iostream>
#include <cmath>

int main(){
    double initSpeed = 0, time = 0;
    double g = 9.81;

    std::cout << "Enter initial speed: ";
    std::cin >> initSpeed;
    std::cout << "Enter time: ";
    std::cin >> time;

    if(initSpeed < 0){
        std::cout << "Initial speed can't be equal or less than 0 " << std::endl;
        exit(EXIT_FAILURE);
    }
    else if(initSpeed > 0){
        std::cout << "The angle at which the body will fly will be equal to " 
            << (asin(g * time / (2 * initSpeed))) * (180 / M_PI) << std::endl;
    }
    else{
        std::cout << "Unknown error was occured." << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}