#include <iostream>

int main(){
    int choice = 0;
    enum weekday { Monday = 1, Tuesday = 2, Wednesday = 3, Thursday = 4, 
        Friday = 5, Saturday = 6, Sunday = 7};

    weekday _weekday;

    std::cout << "Enter digit the appropriate one to the weekday: ";
    std::cin >> choice;

    _weekday = static_cast<weekday>(choice);

    if(choice >= 1 && choice <= 7){
        switch (_weekday){
        case Monday:
            std::cout << "Monday" << std::endl;
            break;
        case Tuesday:
            std::cout << "Tuesday" << std::endl;
            break;
        case Wednesday:
            std::cout << "Wednesday" << std::endl;
            break;
        case Thursday:
            std::cout << "Thursday" << std::endl;
            break;
        case Friday:
            std::cout << "Friday" << std::endl;
            break;
        case Saturday:
            std::cout << "Saturday" << std::endl;
            break;
        case Sunday:
            std::cout << "Sunday" << std::endl;
            break;        
        default:
            break;
        }
    }
    else{
        std::cout << "Invalid value. " << std::endl;
        exit(EXIT_FAILURE);
    }    

    return EXIT_SUCCESS;
}