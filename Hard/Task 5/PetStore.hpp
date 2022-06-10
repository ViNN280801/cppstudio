#pragma once

#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include <algorithm>

// Including libraries for work with files
#include <fstream>

using namespace std;

#define ERR_MSG_INCR_DATA_INPUT "Incorrect data input.\n"
#define ERR_OPEN_FILE "File opening error.\n"

// Base class Animal
class Animal
{
private:
    // Means wolf, penguin, dog etc.
    string ms_kindOfAnimal{""};

    // 0 (false) - male, != 0 (true) - female
    // mb -> member, bool
    bool mb_sex{false};

    // ms -> member, string
    string ms_name{""};

protected:
    /* Cleaning up Animal data members:
    ms_kindOfAnimal = ""
    mb_sex = false
    ms_name = ""
    */
    virtual inline void cleanup()
    {
        ms_kindOfAnimal.clear();
        mb_sex = false;
        ms_name.clear();
    }

public:
    // Getting sex of animal
    inline bool getSex() const { return mb_sex; };

    // Setting sex of animal
    inline void setSex(const bool &__sex) { mb_sex = __sex; };

    // Default (Zero-argument) ctor
    explicit Animal() { cleanup(); };

    // Ctor with params
    explicit Animal(const string &__kind, const bool &__sex, const string &__name)
    {
        ms_kindOfAnimal = __kind;
        mb_sex = __sex;
        ms_name = __name;
    }

    // Copy ctor
    explicit Animal(const Animal &animal)
    {
        // Copying data from class obj
        mb_sex = animal.mb_sex;
    }

    // Move ctor
    explicit Animal(Animal &&animal)
    {
        // Copying data from class obj
        ms_kindOfAnimal = animal.ms_kindOfAnimal;
        mb_sex = animal.mb_sex;
        ms_name = animal.ms_name;
        // Zeroing out source (class obj)
        animal.cleanup();
    }

    // Assignment operator
    Animal &operator=(const Animal &animal)
    {
        // Checking self-assigning
        if (this == &animal)
            return *this;

        // Copying data from class obj
        ms_kindOfAnimal = animal.ms_kindOfAnimal;
        mb_sex = animal.mb_sex;
        ms_name = animal.ms_name;

        return *this;
    }

    // Move assignment operator
    Animal &operator=(Animal &&animal) noexcept
    {
        if (this == &animal)
            return *this;

        // Zeroing out this obj
        cleanup();

        // Copying data from class obj
        ms_kindOfAnimal = animal.ms_kindOfAnimal;
        mb_sex = animal.mb_sex;
        ms_name = animal.ms_name;

        // Zeroing out class obj from parameter
        animal.cleanup();

        return *this;
    }

    // Returns sex as string like following:
    // false - male (= 0)
    // true - female (!= 0)
    string getSexAsString() const
    {
        switch (static_cast<int>(mb_sex))
        {
        case 0:
            return "Male";
            break;
        case 1:
            return "Female";
            break;
        default:
            return "Not defined";
            break;
        }
    }

    // Virtual destructor
    virtual ~Animal(){};

    // Getting name
    inline string getName() const { return ms_name; }

    // Setting name
    inline void setName(const string &__name) { ms_name = __name; }

    // Getting kind of animal
    inline string getKind() const { return ms_kindOfAnimal; }

    // Setting kind of animal
    inline void setKind(const string &__kind) { ms_kindOfAnimal = __kind; }

    /* Getting kind of animal with int parameter, which is defining kind
    1 - Wolf
    2 - Penguin
    3 - Dog */
    string setKindWithIntParam(const int &__kind) const
    {
        if (__kind == 1)
            return "Wolf";
        else if (__kind == 2)
            return "Penguin";
        else if (__kind == 3)
            return "Dog";
        else
            return "Unknown";
    }
};

// Derive class of the Animal class. Pets sale.
class PetStore final : public Animal
{
private:
    // Price list:
    // Letter 'k' means constant
    const float kpriceWolf = 79.95f;
    const float kpricePenguin = 145.89f;
    const float kpriceDog = 44.99f;

    // Count of animals in the store
    // mi -> member, int
    int mi_count{};

    // Price of 1 animal
    // mf -> member, float
    float mf_price{};

protected:
    /* Cleaning up PetStore data members:
    mi_count = 0
    mf_price = 0.0f */
    virtual inline void cleanup() override final
    {
        mi_count = 0;
        mf_price = 0.0f;
    }

    // Returns price of certain kind of animal as float
    float getPriceOfKindOfAnimal(const string &__kindOfAnimal) const
    {
        if (__kindOfAnimal == "Wolf" || __kindOfAnimal == "wolf")
            return kpriceWolf;
        else if (__kindOfAnimal == "Penguin" || __kindOfAnimal == "penguin")
            return kpricePenguin;
        else if (__kindOfAnimal == "Dog" || __kindOfAnimal == "dog")
            return kpriceDog;
        else
            return 0.0f;
    }

    // Returns total cost (price * count)
    inline float calcTotalCost(const string &__kindOfAnimal, const int &__count) const
    {
        if (getPriceOfKindOfAnimal(__kindOfAnimal) != 0.0f)
        {
            return (getPriceOfKindOfAnimal(__kindOfAnimal) * static_cast<float>(__count));
        }
        else
            return 0.0f;
    }

    // Zeroing out uint16_t variable and clearing console
    inline void clearValAndConsole(uint16_t &__value)
    {
        __value = 0;
        system("clear");
    }

    // Generating random string and returns it
    string generateRandomString(const size_t lenght) const
    {
        static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        string rndmString{};
        // Reserving memory for tmp string
        rndmString.reserve(lenght);

        for (size_t iter = 0; iter < lenght; iter++)
        {
            rndmString += alphabet[rand() % (sizeof(alphabet) - 1)];
        }

        return rndmString;
    }

    // Writing vector of PetStore objects to file "PetStore.txt"
    void writeDataToFile(const vector<PetStore> &petVec) const
    {
        // Declaring file output stream instance and name of file
        ofstream fout;
        const char *fileName{"PetStore.txt"};

        try
        {
            // Opening file
            fout.open(fileName);

            for (size_t iter = 0; iter < petVec.size(); iter++)
            {
                if (petVec[iter].calcTotalCost(petVec[iter].getKind(), petVec[iter].getCount()) != 0.0f)
                {
                    fout << "\n==== ==== Animal #" << iter + 1 << " ==== ==== " << endl;
                    fout << "Kind of animal: " << petVec[iter].getKind() << endl;
                    fout << "Sex: " << petVec[iter].getSexAsString() << endl;
                    fout << "Name: " << petVec[iter].getName() << endl;
                    fout << "Price: " << petVec[iter].getPrice() << "$" << endl;
                    fout << "Count: " << petVec[iter].getCount() << endl;
                    fout << "Total cost: " << petVec[iter].calcTotalCost(petVec[iter].getKind(), petVec[iter].getCount()) << "$" << endl;
                    fout << "==== ==== ==== ==== ==== ====\n\n";
                }
                else
                {
                    cout << "Total cost calculation error. " << endl;
                    exit(EXIT_FAILURE);
                }
            }
            cout << "Data was successfully written into file - " << fileName << endl;
        }
        catch(const ofstream::failure &err)
        {
            cout << ERR_OPEN_FILE;
            cerr << err.what() << '\n';
            cerr << "Code of error: " << err.code() << endl;
        }

        fout.close();
    }

    // Reading data from file to string
    void readDataFromFile()
    {
        // Declaring file input stream instance and name of file
        ifstream fin;
        const char *fileName{"PetStore.txt"};

        fin.exceptions(ifstream::badbit | ifstream::failbit);

        try
        {
            // Opening file
            fin.open(fileName);

            // Writing data to sting
            fin.seekg(0, ios::end);
            size_t sizeOfFile = fin.tellg();
            string buffer(sizeOfFile, ' ');
            fin.seekg(0);
            fin.read(&buffer[0], sizeOfFile);

            cout << buffer;
        }
        catch (const ifstream::failure &err)
        {
            cout << ERR_OPEN_FILE;
            cerr << err.what() << endl;
            cerr << "Code of error: " << err.code() << endl;
        }

        fin.close();
    }

public:
    // Default (Zero-argument) ctor
    explicit PetStore() { cleanup(); }

    // Ctor with params
    explicit PetStore(const int &__count, const float &__price)
    {
        mi_count = __count;
        mf_price = __price;
    }

    // Copy ctor
    explicit PetStore(const PetStore &__petStore)
    {
        // Copying data from class obj
        mi_count = __petStore.mi_count;
        mf_price = __petStore.mf_price;
    }

    // Move ctor
    explicit PetStore(PetStore &&__petStore)
    {
        // Copying data from class obj
        mi_count = __petStore.mi_count;
        mf_price = __petStore.mf_price;

        // Zeroing out source (class obj)
        __petStore.cleanup();
    }

    // Assignment operator
    PetStore &operator=(const PetStore &__petStore)
    {
        // Check self-assigning
        if (this == &__petStore)
            return *this;

        // Copying data from class obj
        mi_count = __petStore.mi_count;
        mf_price = __petStore.mf_price;

        return *this;
    }

    // Move assignment operator
    PetStore &operator=(PetStore &&__petStore) noexcept
    {
        // Check self-assigning
        if (this == &__petStore)
            return *this;

        // Zeroing out this obj
        cleanup();
        // Copying data from class obj
        mi_count = __petStore.mi_count;
        mf_price = __petStore.mf_price;
        // Zeroing out class obj from parameter
        __petStore.cleanup();

        return *this;
    }

    // Virtual destructor
    virtual ~PetStore(){};

    // Getting count of animals
    inline int getCount() const { return mi_count; }

    // Setting count of animals
    inline void setCount(const int &__count) { mi_count = __count; }

    // Gettting price of animal
    inline float getPrice() const { return mf_price; }

    // Setting price of animal
    inline void setPrice(const float &__price) { mf_price = __price; }

    // Input data from keyboard
    vector<PetStore> inputData()
    {
        uint16_t choice{};

        cout << "Enter count of animals: ";
        cin >> choice;
        setCount(choice);
        uint16_t size{choice};
        clearValAndConsole(choice);

        // Declaring vector of PetStore objects with known size
        vector<PetStore> petVec(size);

        for (uint16_t iter = 0; iter < size; iter++)
        {
            petVec[iter].setCount(1);

            cout << "Kinds of animal:\n1. Wolf\n2. Penguin\n3. Dog " << endl;
            cout << "Enter kind: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                petVec[iter].setKind("Wolf");
                break;
            case 2:
                petVec[iter].setKind("Penguin");
                break;
            case 3:
                petVec[iter].setKind("Dog");
                break;
            default:
                cout << ERR_MSG_INCR_DATA_INPUT;
                petVec[iter].setKind("Unknown");
                break;
            }

            if (petVec[iter].getKind() == "Unknown")
                exit(EXIT_FAILURE);
            clearValAndConsole(choice);

            cout << "Animal's sex: \n1. Male\n2. Female\nEnter sex: ";
            cin >> choice;

            if (choice < 1 || choice > 2)
            {
                cout << ERR_MSG_INCR_DATA_INPUT;
                exit(EXIT_FAILURE);
            }

            petVec[iter].setSex(static_cast<bool>(--choice));
            clearValAndConsole(choice);

            cout << "Enter name of animal: ";
            string tmp{};
            cin >> tmp;
            petVec[iter].setName(tmp);
            tmp.clear();
            system("clear");

            petVec[iter].setPrice(petVec[iter].getPriceOfKindOfAnimal(petVec[iter].getKind()));
        }

        return petVec;
    }

    // Showing all characteristics of certain animal of current object
    void showData() const
    {
        if (calcTotalCost(getKind(), getCount()) != 0.0f)
        {
            cout << "\n==== ==== Animal ==== ==== " << endl;
            cout << "Kind of animal: " << getKind() << endl;
            cout << "Sex: " << getSexAsString() << endl;
            cout << "Name: " << getName() << endl;
            cout << "Price: " << getPrice() << "$" << endl;
            cout << "Count: " << getCount() << endl;
            cout << "Total cost: " << calcTotalCost(getKind(), getCount()) << "$" << endl;
            cout << "==== ==== ==== ==== ==== ====\n\n";
        }
        else
        {
            cout << "Total cost calculation error. " << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Showing all characteristics of certain animal from vector of objects
    void showData(const vector<PetStore> &petVec) const
    {
        for (size_t iter = 0; iter < petVec.size(); iter++)
        {
            if (petVec[iter].calcTotalCost(petVec[iter].getKind(), petVec[iter].getCount()) != 0.0f)
            {
                cout << "\n==== ==== Animal #" << iter + 1 << " ==== ==== " << endl;
                cout << "Kind of animal: " << petVec[iter].getKind() << endl;
                cout << "Sex: " << petVec[iter].getSexAsString() << endl;
                cout << "Name: " << petVec[iter].getName() << endl;
                cout << "Price: " << petVec[iter].getPrice() << "$" << endl;
                cout << "Count: " << petVec[iter].getCount() << endl;
                cout << "Total cost: " << petVec[iter].calcTotalCost(petVec[iter].getKind(), petVec[iter].getCount()) << "$" << endl;
                cout << "==== ==== ==== ==== ==== ====\n\n";
            }
            else
            {
                cout << "Total cost calculation error. " << endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    // Filling random data to PetStore vector
    vector<PetStore> rndmFillingVec(const size_t &__lenght)
    {
        // Using current time as seed for random generator
        srand(time(nullptr));

        // Declaring vector of PetStore objects with size = __lenght
        vector<PetStore> petVec(__lenght);
        PetStore pet;

        // Filling random data into vector of objects using loop 'for'
        for (size_t iter = 0; iter < __lenght; iter++)
        {
            petVec[iter].setKind(setKindWithIntParam(1 + rand() % 3));
            petVec[iter].setSex(static_cast<bool>(0 + rand() % 2));
            petVec[iter].setName(generateRandomString(5 + rand() % 20));
            petVec[iter].setPrice(10.00f + static_cast<float>(rand() % 200));
            petVec[iter].setCount(1 + rand() % 100);
        }

        return petVec;
    }

    // Showing menu
    void showMenu()
    {
        vector<PetStore> petVec;
        uint16_t choice{};

        system("clear");

        while (!choice)
        {
            cout << "1. Custom data input \n2. Random input\n3. Read data from file\n4. Exit from program " << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                char alphaChoice{};

                // Zeroing out 'choice' and clear the console
                clearValAndConsole(choice);

                // Input data from console
                petVec = inputData();

                // Output data to console
                showData(petVec);

                cout << "Do you want to write this data into a file? " << endl;
                cout << "Y/y - Yes\nN/n - No\nEnter your choice: ";
                cin >> alphaChoice;

                switch (alphaChoice)
                {
                case 'Y':
                    writeDataToFile(petVec);
                    break;
                case 'y':
                    writeDataToFile(petVec);
                    break;
                case 'N':
                    cout << "Exiting ... " << endl;
                    exit(EXIT_SUCCESS);
                case 'n':
                    cout << "Exiting ... " << endl;
                    exit(EXIT_SUCCESS);
                default:
                    cout << ERR_MSG_INCR_DATA_INPUT;
                    exit(EXIT_FAILURE);
                    break;
                }
                getchar();
                getchar();
                system("clear");
            }
            else if (choice == 2)
            {
                char alphaChoice{};

                // Zeroing out 'choice' and clear the console
                clearValAndConsole(choice);

                // Creating size of vector of PetStore objects
                size_t lenght{};

                cout << "Enter count of animals: ";
                cin >> lenght;

                // Filling with random data new vector varibale
                vector<PetStore> petVec = rndmFillingVec(lenght);

                // Output data to console
                showData(petVec);

                cout << "Do you want to write this data into a file? " << endl;
                cout << "Y/y - Yes\nN/n - No\nEnter your choice: ";
                cin >> alphaChoice;

                switch (alphaChoice)
                {
                case 'Y':
                    writeDataToFile(petVec);
                    break;
                case 'y':
                    writeDataToFile(petVec);
                    break;
                case 'N':
                    cout << "Exiting ... " << endl;
                    exit(EXIT_SUCCESS);
                case 'n':
                    cout << "Exiting ... " << endl;
                    exit(EXIT_SUCCESS);
                default:
                    cout << ERR_MSG_INCR_DATA_INPUT;
                    exit(EXIT_FAILURE);
                    break;
                }
                getchar();
                getchar();
                system("clear");
            }
            else if (choice == 3)
            {
                // Zeroing out 'choice' and clear the console
                clearValAndConsole(choice);

                readDataFromFile();
                getchar();
                getchar();
                system("clear");
            }
            else if (choice == 4)
            {
                break;
            }
            else
            {
                cout << ERR_MSG_INCR_DATA_INPUT;
                exit(EXIT_FAILURE);
            }
        }
        cout << "Exiting ... " << endl;
        exit(EXIT_SUCCESS);
    }
};