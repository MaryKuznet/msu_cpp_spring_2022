#pragma once
#include <iostream>

// Варианты ошибок
enum ExceptionType
    {
        Not_enough_args,
        Only_one_bracket,
        Not_number,
        Bad_number,
    };

// Класс ошибок
class MyError
{
public:
    ExceptionType error_type;
    int line_;
    MyError(const ExceptionType& error, int line): error_type(error), line_(line){}
};
