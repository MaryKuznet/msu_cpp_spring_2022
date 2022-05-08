#include "format.hpp"
#include <sstream>

// С помощью этих 2-х функций мы вытаскиваем нужный параметр, если он есть
template <class T = ExceptionType>
void param(std::stringstream& str, int number, T arg = ExceptionType::Not_enough_args){
    if (number == 0 && typeid(arg) != typeid(ExceptionType))
        str << arg;
    else
        throw MyError(ExceptionType::Not_enough_args, __LINE__);
}

template <class T, class... ArgsT>
void param(std::stringstream& str, int number, T arg, ArgsT ...args)
{
    if (number == 0)
        str << arg;
    else
    {
        number--;
        param(str, number, args...);
    }
}

// Основная функция format
template <class... ArgsT>
std::string format(const std::string& line, const ArgsT ...args)
{
    std::stringstream new_line;
    int i = 0;
    int n = line.size();

    while (i < n)
    {
        if (line[i] == '}')
            throw MyError(ExceptionType::Only_one_bracket, __LINE__);
        else if (line[i] != '{')
            new_line << line[i];
        else
        {
            i ++;
            if (i == n || line[i] == '}')
                throw MyError(ExceptionType::Not_number, __LINE__);
            std::string digit = "";
            while (line[i] != '}'){
                if (i < n && '0' <= line[i] && line[i] <= '9')
                    digit += line[i];
                else
                    throw MyError(ExceptionType::Bad_number, __LINE__);
                i ++;
            }
            int number_arg = stoi(digit);
            param(new_line, number_arg, args...);
        }
        i++;
    }
    return new_line.str();
}
