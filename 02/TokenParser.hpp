#include <iostream>

typedef long int (*FuncInt)(long int);
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
    void SetStartCallback(std::string (*fb)());

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(std::string (*fe)());

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(long int (*fi)(long int));

    // Устанавливаем callback-функцию для обработки строк.
    void SetStringTokenCallback(int (*fs)(std::string));

    // Парсер строк.
    std::string Parse(const std::string & line);
};