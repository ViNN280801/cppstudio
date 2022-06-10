#include "task6.hpp"

int main(int arc, char* argv[]){
    strManipul stringManip;
    std::string inputStr;

    std::cout << "Enter size of matrix (matrix is square, just enter one number): ";
    std::cin >> inputStr;
    bool isChecked { stringManip.f_isCheckedStr(inputStr) };

    if(isChecked == true){
        // Constant value for size of matrix
        const UINT16 kmatrixSize { stringManip.f_stoui16(inputStr, kmatrixSize) };
        std::cout << kmatrixSize << std::endl;
    }

    return EXIT_SUCCESS;
}
