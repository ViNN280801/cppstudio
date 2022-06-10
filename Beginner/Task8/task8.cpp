#include <iostream>
#include <cstring>

int mystrlen(std::string); 

class Titletable{
    std::string templts[3]{"* Laboratory work #1","* Completed by st. from group ","* " };
    int maxlen = 0;

public:
    Titletable(std::string surname, std::string name, std::string patronymic, std::string group);
  
    int findMaxLength();
    void printTable(int);

    int getMaxLength(){
        return maxlen;
    }
};

int main()
{
    std::string surname, name, partonymic, group;
    std::cout << "Enter surname: ";
    std::cin >> surname;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter patronymic: ";
    std::cin >> partonymic;
    std::cout << "Enter number of group: ";
    std::cin >> group;

    Titletable cTitletable(surname, name, partonymic, group);
    cTitletable.printTable(cTitletable.getMaxLength());
}

Titletable::Titletable(std::string surname, std::string name, 
    std::string patronymic, std::string group){
    templts[1] += group;
    templts[2] = templts[2] + surname + " " + name + " " + patronymic;
    maxlen = findMaxLength();
}
 
void Titletable::printTable(int){
    for(int i = 0; i < maxlen; i++) 
        std::cout << "*";
    
    std::cout << "**\n";

    for(int i = 0; i < 3; i++){
        std::cout << templts[i];

        int spaces = maxlen - mystrlen(templts[i]);
        for(int counter = 0; counter < spaces; counter++) 
            std::cout << " ";

        std::cout << " *\n";
    }
    for(int i = 0; i < maxlen; i++) 
        std::cout << "*";
    
    std::cout << "**\n";
}

int Titletable::findMaxLength(){
    int max = 0;

    for(int i = 0; i < 3; i++) 
        if(mystrlen(templts[i]) > max) 
            max = mystrlen(templts[i]);

    return max;
}

int mystrlen(std::string str){
    int counter = 0;

    for(int i = 0; str[i];){
        (static_cast<int>(str[i])<0) ? i+=2 : i++;

        counter++;
    }

    return counter;    
}
