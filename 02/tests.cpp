#include <iostream>
#include "TokenParser.cpp"
#include <gtest/gtest.h>

class TestTokenParser : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

//Тестируем, что установка начальной функции проходит нормально
TEST_F(TestTokenParser, Test1){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fb, nullptr);

    parser.SetStartCallback([](){return std::string("Begin");});
    ASSERT_EQ(parser.fb(), "Begin");

    parser.SetStartCallback(nullptr);
    ASSERT_EQ(parser.fb, nullptr);
}

//Тестируем, что установка конечной функции проходит нормально
TEST_F(TestTokenParser, Test2){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fe, nullptr);

    parser.SetEndCallback([](){return std::string("End");});
    ASSERT_EQ(parser.fe(), "End");

    parser.SetEndCallback(nullptr);
    ASSERT_EQ(parser.fe, nullptr);
}

//Тестируем, что установка функции для токенов цифр проходит нормально
TEST_F(TestTokenParser, Test3){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fi,nullptr);

    parser.SetDigitTokenCallback([](uint64_t x){return uint64_t(x*x);});
    ASSERT_EQ(parser.fi(12), 144);

    parser.SetDigitTokenCallback(nullptr);
    ASSERT_EQ(parser.fi, nullptr);
}

//Тестируем, что установка функции для токенов строк проходит нормально
TEST_F(TestTokenParser, Test4){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fs,nullptr);

    parser.SetStringTokenCallback([](std::string x){return int(x.size());});
    ASSERT_EQ(parser.fs("abc"),3);

    parser.SetStringTokenCallback(nullptr);
    ASSERT_EQ(parser.fs, nullptr);
}

//Тестируем функцию парсинга
// Для тестирование устанавливаем колбеками функции, ктр что-то выводят и смотрим на вывод после парсинга
TEST_F(TestTokenParser, Test5){
    TokenParser parser = TokenParser();
    std::string line = "abc +412 2 abc 10 a";

    testing::internal::CaptureStdout();
    parser.Parse(line);
    std::string out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "");

    parser.SetStartCallback([](){std::cout << "Begin "; return std::string("Begin");});
    testing::internal::CaptureStdout();
    parser.Parse(line);
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin ");

    parser.SetEndCallback([](){std::cout << "End" << std::endl; return std::string("End");});
    testing::internal::CaptureStdout();
    parser.Parse(line);
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin End\n");

    parser.SetDigitTokenCallback([](uint64_t x){std::cout << "d:"<< x << " "; return x;});
    testing::internal::CaptureStdout();
    parser.Parse(line);
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin d:2 d:10 End\n");

    parser.SetStringTokenCallback([](std::string x){std::cout << "w:" << x << " "; return int(x.size());});
    testing::internal::CaptureStdout();
    parser.Parse(line);
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin w:abc w:+412 d:2 w:abc d:10 w:a End\n");
}

// Тесты крайних случаев
// Для тестирование устанавливаем колбеками функции, ктр что-то выводят и смотрим на вывод после парсинга
TEST_F(TestTokenParser, Test6){
    TokenParser parser = TokenParser();
    parser.SetStartCallback([](){std::cout << "Begin "; return std::string("Begin");});
    parser.SetEndCallback([](){std::cout << "End" << std::endl; return std::string("End");});
    parser.SetDigitTokenCallback([](uint64_t x){std::cout << "d:"<< x << " "; return x;});
    parser.SetStringTokenCallback([](std::string x){std::cout << "w:" << x << " "; return int(x.size());});

    // Тест парсинга пустой строки
    testing::internal::CaptureStdout();
    parser.Parse("");
    std::string out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin End\n");

    // Тест строки из пробельных символов
    testing::internal::CaptureStdout();
    parser.Parse("   \t  ");
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin End\n");

    // Тест односивольной строки токена "1"
    testing::internal::CaptureStdout();
    parser.Parse("1");
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin d:1 End\n");

    // Тест односивольной строки токена "a"
    testing::internal::CaptureStdout();
    parser.Parse("a");
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin w:a End\n");

    // Тест строки с токенами вида 42str
    testing::internal::CaptureStdout();
    parser.Parse("str 42str s4s str42 42");
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin w:str w:42str w:s4s w:str42 d:42 End\n");

    // Тесты для проверки максимальных значений unit64
    testing::internal::CaptureStdout();
    parser.Parse("18446744073709551615 abc");
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "Begin d:18446744073709551615 w:abc End\n");

    ASSERT_ANY_THROW(parser.Parse("18446744073709551616"));
    ASSERT_ANY_THROW(parser.Parse("36893488147419103232"));

    // Тесты смешанных строк
    parser.SetStartCallback(nullptr);
    testing::internal::CaptureStdout();
    parser.Parse("1 1a b2 2+1 abc 245");
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "d:1 w:1a w:b2 w:2+1 w:abc d:245 End\n");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}