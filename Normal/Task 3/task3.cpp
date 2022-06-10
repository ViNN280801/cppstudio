#include <iostream>
#include <vector>
#include <cstdlib>

void printVector(std::vector<int> vec, int length){
    for(int val : vec)
        std::cout << val << "\t";

    std::cout << std::endl;
}

void fillVector(std::vector<int> vec, int length){
    for(int i = 0; i < length; i++){
        int val = rand() % 10 + 1;
        vec.push_back(val);
    }
}

void fillMatrix(int** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            matrix[i][j] = rand() % INT16_MAX;
}

void printMatrix(int** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            std::cout << matrix[i][j] << "\t";

        std::cout << std::endl;       
    }
}

int main(){
    srand(time(NULL));

    int rows = 0, cols = 0;
    int** matrix = NULL;

    std::cout << "Enter count of rows: ";
    std::cin >> rows;
    if(rows == 0 || rows < 0){
        std::cout << "Error. Count of rows can't be equals 0 or less than 0. " << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Enter count of columns: ";
    std::cin >> cols;
    if(cols == 0 || cols < 0){
        std::cout << "Error. Count of columns can't be equals 0 or less than 0. " << std::endl;
        exit(EXIT_FAILURE);
    }

    if(cols < rows){
        int tmp = 0;
        tmp = rows;
        rows = cols;
        cols = tmp;
    }

    matrix = (int**)calloc(rows, sizeof(int*));
    if(!matrix){
        std::cout << "Allocation memory error." << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        for(int i = 0; i < cols; i++){
            matrix[i] = (int*)calloc(cols, sizeof(int));

            if(!matrix[i]){
                std::cout << "Allocation memory error." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    fillMatrix(matrix, rows, cols);
    printMatrix(matrix, rows, cols);

    int vecLength = 0;
    std::cout << "Enter vector length: ";
    std::cin >> vecLength;
    
    if(vecLength < rows){
        std::cout << "Unable to find the product. Vector length can't be less than rows." 
            << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<int> vec;
    for(int i = 0; i < vecLength; i++)
        vec.push_back((rand() % 10 + 1));
    printVector(vec, vecLength);

    int multVec[vecLength];
    for(int i = 0; i < rows; i++){
        multVec[i] = 0;
        for(int j = 0; j < cols; j++)
            multVec[i] += matrix[i][j] * vec[j];
    }

    std::cout << "\nProduct result: " << std::endl;
    for(int i = 0; i < vecLength; i++){
        if(multVec[i] < 0 || multVec[i] >= INT32_MAX)
            multVec[i] = 0;

        std::cout << multVec[i] << "\t";
    }
    std::cout << std::endl;

    for(int i = 0; i < rows; i++)
        delete[] matrix[i];

    delete[] matrix;

    return EXIT_SUCCESS;
}