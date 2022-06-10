#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <exception>

#define ERRMSG "Error: "

bool checkEnteredString(std::string str){
    if(str[0] == '-'){
        std::cout << "Your number is negative." << std::endl;
        return false;
    }
    if(str.empty()){
        std::cout << ERRMSG << "Your string is empty." << std::endl;
        return false;
    }
    if(!(std::all_of(str.begin(), str.end(), ::isdigit))){
        std::cout << ERRMSG << "Your string does not contains only digits." << std::endl;
        return false;
    }
    else if(std::all_of(str.begin(), str.end(), ::isdigit))
        return true;

    return false;
}

inline int returnResult(std::string str){
    int result {};

    try {
        result = std::stoi(str);
    }  catch (const std::exception& ex) {
        std::cout << ERRMSG << "Function std::" << ex.what() << " -> Out of range.\nResult is ";
    }

    return result;
}

int main(int argc, char* argv[]){
    std::string str {};
    int* pArr { new int[1] };
    int* pCpy = nullptr;
    bool flag {};
    size_t arrSize { 0 };

    while(str[0] != '-'){
        std::cout << "Enster a number: ";
        std::cin >> str;

        flag = checkEnteredString(str);
        if(flag){
            if(arrSize == 0){
                *(pArr + arrSize) = returnResult(str);
                std::cout << *(pArr + arrSize) << " " << std::endl;;
                arrSize++;
            }
            else{
                pCpy = new int[arrSize + 1];
                for(size_t i = 0; i < arrSize; i++)
                    *(pCpy + i) = *(pArr + i);
                *(pCpy + arrSize) = returnResult(str);

                delete[] pArr;
                pArr = nullptr;

                pArr = new int[arrSize + 1];
                for(size_t i = 0; i < (arrSize + 1); i++){
                    *(pArr + i) = *(pCpy + i);
                    std::cout << *(pArr + i) << " ";
                }
                std::cout << std::endl;

                delete[] pCpy;
                pCpy = nullptr;

                arrSize++;
            }
        }
    }

    delete[] pArr;
    pArr = nullptr;

    return EXIT_SUCCESS;
}
