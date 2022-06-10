#include <iostream>
#include <cstdlib>
#include <cmath>

void printNumbers(double* numbers, int size){
    for(int i = 1; i <= size; i++){
        std::cout << numbers[i] << "\t";

        if(i % 5 == 0)
            std::cout << std::endl;
    }
}

double sumSquareOfNumsWhichGreaterThanAbsValue(double* numbers, int size, double absVal){
    double sum = 0;

    for(int i = 0; i < size; i++)
        if(numbers[i] > absVal)
            sum += pow(numbers[i], 2);

    return sum;
}

int main(){
    double* numbers = NULL;
    double absoluteValue = 0;
    int sizeOfArray = 0;

    std::cout << "Enter size of array: ";
    std::cin >> sizeOfArray;
    if(sizeOfArray <= 0){
        std::cout << "Size can't be less or equals 0." << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        numbers = (double*)calloc(sizeOfArray, sizeof(double));

        if(!numbers){
            std::cout << "Allocation memory error." << std::endl;
            exit(EXIT_FAILURE);
        }
        else{
            for(int i = 0; i <= sizeOfArray; i++)
                numbers[i] = rand() % INT16_MAX;

            std::cout << "Enter absolute value, which array can't be greater: ";
            std::cin >> absoluteValue;

            if(absoluteValue < 0)
                absoluteValue = abs(absoluteValue);

            std::cout << "\nList of numbers: \n";
            std::cout << "##### ##### ##### ##### ##### ##### #####\n";
            printNumbers(numbers, sizeOfArray);
            std::cout << "##### ##### ##### ##### ##### ##### #####\n\n";

            std::cout << "Sum of squares of those numbers whose absolute value exceeds the value " 
                << absoluteValue << " is " 
                << sumSquareOfNumsWhichGreaterThanAbsValue(numbers, sizeOfArray, absoluteValue) 
                << std::endl << std::endl;
        }
    }

    delete[] numbers;

    return EXIT_SUCCESS;
}