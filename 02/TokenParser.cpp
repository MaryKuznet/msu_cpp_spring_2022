#include "TokenParser.hpp"
#include <string>
#include <iostream>

void TokenParser::SetStartCallback(FuncBeginEnd fb){
    this->fb = fb;
}

void TokenParser::SetEndCallback(FuncBeginEnd fe){
    this->fe = fe;
}

void TokenParser::SetDigitTokenCallback(FuncInt fi){
    this->fi = fi;
}

void TokenParser::SetStringTokenCallback(FuncString fs){
    this->fs = fs;
}

void TokenParser::Parse(const std::string & line){

    if (fb != nullptr) {
        fb();
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
                long int digit = 0;
                try{
                    digit = std::stoull(word);
                }
                catch(std::out_of_range const& e){
                    isdig = false;
                    if (fs != nullptr) {
                        fs(word);
                    }
                }
                if ((isdig == true) && (fi != nullptr)){
                    fi(digit);
                }
            }else{
                if (fs != nullptr) {
                    fs(word);
                }
            }
        }
        ++i;
    };

    if (fe != nullptr) {
        fe();
    }
}