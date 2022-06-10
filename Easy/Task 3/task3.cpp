#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>

#define BUFF_SIZE 256
#define INTEGER_MAX_VALUE 2147483647

int findMinFromDigitArray(int* arr, int length){
    int min = 9;

    for(int i = 1; i <= length; i++)
        if(min > arr[i])
            min = arr[i];

    return min;
}

int findMaxFromDigitArray(int* arr, int length){
    int max = 0;

    for(int i = 1; i <= length; i++)
        if(max < arr[i])
            max = arr[i];

    return max;
}

int main(){
    int number = 0;
    char* str = (char*)calloc(BUFF_SIZE, sizeof(char));

    if(!str){
        std::cout << "Allocation memory error." << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        std::cout << "Enter number: ";
        std::cin >> str;

        short int length = strlen(str);

        str = (char*)realloc(str, length);
        int* digitArr = (int*)calloc(length, sizeof(int));

        if(!digitArr){
            std::cout << "Allocation memory error." << std::endl;
            exit(EXIT_FAILURE);
        }
        else{
            for(short int i = 0; i < length; i++){
                if(isalpha(str[i])){
                    std::cout << str[i] << " isn't a number. " << std::endl;
                    exit(EXIT_FAILURE); 
                } 
                else if(!isalpha(str[i])){
                    number = atoi(str);

                    if(number == INTEGER_MAX_VALUE || number < 0){
                        std::cout << 
                            "You have exceeded the maximum value of integer or number is negative."
                            << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    else continue;
                }
                else{
                    std::cout << "Unknown error was occured. " << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            for(short int i = 1; i <= length; i++){
                if(i == 1){
                    std::cout << i << " digit is " << (int)(number / pow(10, length - i)) 
                        << std::endl;
                    digitArr[i] = (int)(number / pow(10, length - i));
                }
                else if(i > 1){
                    std::cout << i << " digit is " << (int)(number / pow(10, length - i)) % 10 
                        << std::endl;

                    digitArr[i] = (int)(number / pow(10, length - i)) % 10;
                }
                else{
                    std::cout << "Unknown error was occured. " << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            std::cout << "\n##################################################\n";
            std::cout << "Min value is " << findMinFromDigitArray(digitArr, length) << std::endl;
            std::cout << "Max value is " << findMaxFromDigitArray(digitArr, length) << std::endl;
            std::cout << "##################################################\n\n";

            delete[] digitArr;
        }
    }
    delete[] str;

    return EXIT_SUCCESS;
}