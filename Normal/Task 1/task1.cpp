#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>

#define TIME_STRING_SIZE 20

std::string readFile(const std::string& filename){
    std::ifstream fin(filename);

    fin.seekg(0, std::ios::end);
    size_t size = fin.tellg();
    std::string str(size, ' ');

    fin.seekg(0);
    fin.read(&str[0], size);

    return str;
}

bool writeToFile(const std::string log){
    time_t rawtime;
    struct tm* timeinfo;
    char currentTime[TIME_STRING_SIZE];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(currentTime, TIME_STRING_SIZE, "%d.%m.%Y %H:%M:%S", timeinfo);

    std::string __curTimeStr(currentTime);
    std::string logfilename = __curTimeStr + ".log";
    std::ofstream fout(logfilename);
    fout << log;
    fout.close();

    std::cout << "Log file " << logfilename << " was successfully created." << std::endl;

    return false;
}

int main(){
    std::string log = " ";
    std::string filename = " ";

    std::cout << "Enter name of file: ";
    std::cin >> filename; 
    
    std::ifstream fin(filename);

    if(!fin.is_open()){
        std::cout << "Can't open file." << std::endl;
        exit(EXIT_FAILURE);
    }
    else{
        int openBracket = 0, closeBracket = 0;

        std::string symbols = " ";

        symbols = readFile(filename);

        for(int i = 0; i < symbols.length(); i++){
            if(symbols[i] == '{')
                openBracket++;

            if(symbols[i] == '}')
                closeBracket++;
        }

        if(openBracket < closeBracket || openBracket > closeBracket){
            std::cout << "Broken syntax." << std::endl;
            log = "File " + filename + " was checked. Balance of brackets isn't maintened.\n" + 
                "Open brackets = " + std::to_string(openBracket) + "\t" + "Close brackets = " +
                std::to_string(closeBracket) + "\n";

            writeToFile(log);
        }
        else if(openBracket == closeBracket){
            log = "File " + filename + " was checked. Balance of brackets is maintained.\n" + 
            "Open brackets = " + std::to_string(openBracket) + "\t" + "Close brackets = " +
            std::to_string(closeBracket) + "\n";

            writeToFile(log);
        }
    }
    fin.close();

    return EXIT_SUCCESS;
}