#include <iostream>
#include <cstring>
#include <algorithm>
#include <exception>

using UINT16 = unsigned short int;  // Using aliase for define new type

class strManipul{
private:
    const char* kerrmsg { "Error: " };  // k - "konstant" from German -> constant value error message

public:
    strManipul() {};  // Constructor
    virtual ~strManipul() {}; // Virtual destructor

    // Returns true if string is not empty
    const bool f_isEmpty(const std::string& str){
        if(!str.empty())
            return true;
        else{
            std::cout << kerrmsg << "your input is empty. " << std::endl;
            return false;
        }
    }

    // Returns true if string is contains digits
    const bool f_isDigits(const std::string& str){
        if(std::all_of(str.begin(), str.end(), ::isdigit))
            return true;
        else{
            std::cout << kerrmsg << "your input doesn't contains digits. " << std::endl;
            return false;
        }
    }

    // Returns true if string is not contains spaces
    const bool f_isSpaces(const std::string& str){
        if(!(str.find(' ') != std::string::npos))
            return true;
        else{
            std::cout << kerrmsg << "input can't contains the spaces. " << std::endl;
            return false;
        }
    }

    // Returns true if string is complex checked
    const bool f_isCheckedStr(const std::string& str){
        bool isChecked { false };

        isChecked = f_isEmpty(str);
        if(isChecked == true){
            isChecked = f_isDigits(str);

            if(isChecked == true){
                isChecked = f_isSpaces(str);

                if(isChecked == true) return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }

    // Returns UINT16 from string conversion
    const UINT16 f_stoui16(const std::string& str, const UINT16 kmatrixSize){
        UINT16* p_stouint16;
        p_stouint16 = const_cast<UINT16*>(&kmatrixSize);
        *p_stouint16 = static_cast<UINT16>(strtoul(str.c_str(), NULL, 0));

        return kmatrixSize;
    }
};
