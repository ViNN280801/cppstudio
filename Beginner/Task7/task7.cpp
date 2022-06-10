#include <iostream>
#include <cstdlib>

int main(){
    char plus = '+';

    for(int i = 0; i < 5; i++){
        for(int j = 5; j > 0; j--){
            if(i == j || i > j)
                std::cout << plus;
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}