#include <iostream>
#include <cerrno>
#include <cmath>

#define COUNT_OF_VARIABLES 4

double calculatingResult(double *arr){
    double resultXi = 0;
    double tmpTangens = tan(arr[3]);

    if(errno == EDOM){
        printf("Tangens isn't defined in this area\n");
        exit(EXIT_FAILURE);
    }
    else{
        resultXi = pow(arr[0], 3) - arr[1] + (arr[2] / (pow(tmpTangens, 2)));
    }
    
    return resultXi;
}

bool countCheck(int count){
    if(count < 0){
        printf("Count of variables X can't be less than 0.\n");
        return false;
    }
    else if(count == 0){
        printf("Count of variables X can't be equals 0.\n");
        return false;
    }
    else if(count > 0)
        return true;
    else{
        printf("Unknown error was occured.\n");
        exit(EXIT_FAILURE);
    }

    return false;
}

int main(){
    int count = 0;

    double *arr = NULL;
    double Xi = 0;
    
    std::cout << "Enter count of variable X: ";
    std::cin >> count;

    int tmpCount = count;

    if(countCheck(count)){
        while(tmpCount > 0){
            arr = (double*)calloc(COUNT_OF_VARIABLES, sizeof(double));

            if(!arr){
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
            }
            else{
                std::cout << "Enter value of variable Z, B and A for X" 
                    << tmpCount << std::endl;
                std::cout << "Z = ";
                std::cin >> arr[0];
                std::cout << "B = ";
                std::cin >> arr[1];
                std::cout << "A = ";
                std::cin >> arr[2];
                std::cout << "Betta = ";
                std::cin >> arr[3];

                tmpCount--;

                if(count > 1){
                    for(int k = 0; k < count; k++){
                        Xi += calculatingResult(arr);
                    }
                    std::cout << "Result of calculating = " << Xi << std::endl;
                }
                else if(count == 1){
                    std::cout << "Result of calculating = " << calculatingResult(arr) << std::endl;
                }
                else{
                    std::cout << "Unknown error was occured. " << std::endl;
                }
            }
        }        
        Xi = 0;

        free(arr);
    }
    else{
        printf("Verification failed.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}