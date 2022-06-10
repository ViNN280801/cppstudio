#include <iostream>
#include <cstring>

#define EXIT_CODE 123456

int main(){
    int num = 0;
    char str[256], *p = str;
    bool flag = true;
    
    std::cout << "Enter a number: ";

    while(num != EXIT_CODE){
        std::cin >> str;

        while(*p){
            if(!isdigit(*p++)){
                std::cout << "You entered not a number\n";
                
                flag = false;
                exit(EXIT_FAILURE);
            }
        }

        if(flag == true){
            num = atoi(str);

            std::cout << char(num) << "\t";
        }
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}