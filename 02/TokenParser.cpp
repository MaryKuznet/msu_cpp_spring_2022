#include "TokenParser.hpp"
#include <string>
#include <iostream>

void TokenParser::SetStartCallback(std::string (*fb)()){
    this->fb = fb;
}

void TokenParser::SetEndCallback(std::string (*fe)()){
    this->fe = fe;
}

void TokenParser::SetDigitTokenCallback(long int (*fi)(long int)){
    this->fi = fi;
}

void TokenParser::SetStringTokenCallback(int (*fs)(std::string)){
    this->fs = fs;
}

std::string TokenParser::Parse(const std::string & line){
    std::string check = "";

    if (fb != nullptr) {
        check += fb() + " ";
    }

    int i = 0;
    bool isdig;
    std::string word;
    int n = line.size();

    while (i<n){

        //Считываем токен и проверяем какой у него тип
        word = "";
        isdig = true;
        while (i<n && !isblank(line[i])){
            word += line[i];
            if (line[i] < '0' || line[i] > '9'){
                isdig = false;
            }
            ++i;
        };

        // Применяем функции к токенам
        if (word != ""){
            if (isdig == true){
                long int digit = std::stol(word);
                std::cout << "Integer: " << digit << std::endl;
                if (fi != nullptr) {
                    check += std::to_string(digit) + ":" + std::to_string(fi(digit)) + " ";
                }
            } else{
                std::cout << "word:"<< word << std::endl;
                if (fs != nullptr) {
                    check += word + ":" + std::to_string(fs(word)) + " ";
                }
            }
        }
        ++i;
    };

    if (fe != nullptr) {
        check += fe();
    };

    return check;
}