#include "TokenParser.cpp"
#include <iostream>

std::string Begin(){
    std::cout << "Begin" <<std::endl;
    return "Begin";
}

std::string End(){
    std::cout << "End" <<std::endl;
    return "End";
}

int ForS(std::string s){
    std::cout << "size = " << s.size() << std::endl;
    return s.size();
}

long int ForD(long int a){
    std::cout << "A^2 = " << a*a << std::endl;
    return a*a;
}

int main(){
    TokenParser parser;
    parser.SetStartCallback(Begin);
    parser.SetEndCallback(End);
    parser.SetStringTokenCallback(ForS);
    parser.SetDigitTokenCallback(ForD);
    std::string line = "abc +412 2 abc 10 a";
    std::cout << parser.Parse(line) << std::endl;;
}