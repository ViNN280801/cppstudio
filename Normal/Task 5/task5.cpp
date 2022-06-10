#include <iostream>
#include <cstdlib>
#include <cstring>
#include <exception>

#define ERR_MSG "Error: "

using std::string, std::cout, std::cin, std::endl;

struct Person{
    string name;
    string surname;
    unsigned short int age;
};

string getName(){
    string name {};

    cout << "Enter name: ";

    try {
        cin >> name;
    }  catch (const std::exception& ex) {
        cout << ERR_MSG << ex.what() << endl;
        exit(EXIT_FAILURE);
    }

    return name;
}

string getSurname(){
    string surname {};

    cout << "Enter surname: ";

    try {
        cin >> surname;
    }  catch (const std::exception& ex) {
        cout << ERR_MSG << ex.what() << endl;
    }

    return surname;
}

int getAge(){
    int age {};

    cout << "Enter an age: ";

    try {
        cin >> age;
    }  catch (const std::exception& ex) {
        cout << ERR_MSG << ex.what() << "\nResult is " << endl;
    }

    return age;
}

bool doChoose(){
    bool flag { false };

    cout << "0. Exit from program.\n1. Enter data." << endl;

    try {
        cin >> flag;
    }  catch (const std::exception& ex) {
        cout << ERR_MSG << ex.what() << "\nResult is " << endl;
    }

    return flag;
}

void showPerson(Person* myPerson, unsigned short int personSize){
    for(unsigned short int i = 0; i < personSize; i++){
        cout << "\n---- ---- Showing data ---- ----" << endl;
        cout << "Name: " << myPerson[i].name << endl;
        cout << "Surname: " << myPerson[i].surname << endl;
        cout << "Age: " << myPerson[i].age << endl;
        cout << "---- ---- End of showing ---- ----\n" << endl;
    }
}

int main(int argc, char* argv[]){
    Person* myPerson = new Person[1];
    unsigned short int personSize { 1 };

    while(doChoose()){
        if(personSize == 1){
            myPerson[personSize - 1].name = getName();
            myPerson[personSize - 1].surname = getSurname();
            myPerson[personSize - 1].age = getAge();

            showPerson(myPerson, personSize);

            personSize++;
        }
        else if (personSize > 1){
            Person* cpyPerson = new Person[personSize - 1];
            for(unsigned short int i = 0; i < (personSize - 1); i++){
                cpyPerson[i].name = myPerson[i].name;
                cpyPerson[i].surname = myPerson[i].surname;
                cpyPerson[i].age = myPerson[i].age;
            }

            delete[] myPerson;
            myPerson = nullptr;

            myPerson = new Person[personSize];
            for(unsigned short int i = 0; i < (personSize - 1); i++){
                myPerson[i].name = cpyPerson[i].name;
                myPerson[i].surname = cpyPerson[i].surname;
                myPerson[i].age = cpyPerson[i].age;
            }

            delete[] cpyPerson;
            cpyPerson = nullptr;

            myPerson[personSize - 1].name = getName();
            myPerson[personSize - 1].surname = getSurname();
            myPerson[personSize - 1].age = getAge();

            showPerson(myPerson, personSize);

            personSize++;
        }
        else{
            cout << ERR_MSG << "Unknown error" << endl;
            break;
        }
    }

    delete[] myPerson;
    myPerson = nullptr;

    return EXIT_SUCCESS;
}
