#include <iostream>

int main(){
    int meters = 0;

    std::cout << "Enter meters: ";
    std::cin >> meters;

    if(meters % 1000 > 0){
        std::cout << meters << " m = " << meters / 1000 << "." << meters % 1000 << " km\n";
    }
    else if(meters == 1000){
        std::cout << meters << " m = " << meters / 1000 << " km\n";
    }
    else if(meters >= 100 && meters < 1000){
        std::cout << meters << " m = 0." << meters % 1000 << " km\n";
    }
    else if(meters >= 10 && meters < 100){
        std::cout << meters << " m = 0.0" << meters % 1000 << " km\n";
    }
    else if(meters >= 1 && meters < 10){
        std::cout << meters << " m = 0.00" << meters % 1000 << " km\n";
    }
    else{
        std::cout << "Unknown error. Try again";

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}