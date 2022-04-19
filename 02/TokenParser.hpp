#pragma once
#include <iostream>

typedef uint64_t (*FuncInt)(uint64_t);
typedef int (*FuncString)(std::string);
typedef std::string (*FuncBeginEnd)();

class TokenParser
{
public:
    FuncInt fi = nullptr;
    FuncString fs = nullptr;
    FuncBeginEnd fb = nullptr;
    FuncBeginEnd fe = nullptr;
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(FuncBeginEnd fb);

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(FuncBeginEnd fe);

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(FuncInt fi);

    // Устанавливаем callback-функцию для обработки строк.
    void SetStringTokenCallback(FuncString fs);

    // Парсер строк.
    void Parse(const std::string & line);
};