#include <iostream>
#include "TokenParser.cpp"
#include <gtest/gtest.h>

class TestTokenParser : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
    TokenParser parser;
};

//Тестируем, что установка начальной функции проходит нормально
TEST_F(TestTokenParser, Test1){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fb,nullptr);
    parser.SetStartCallback([](){return std::string("Begin");});
    ASSERT_EQ(parser.fb(),"Begin");
}

//Тестируем, что установка конечной функции проходит нормально
TEST_F(TestTokenParser, Test2){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fe,nullptr);
    parser.SetEndCallback([](){return std::string("End");});
    ASSERT_EQ(parser.fe(),"End");
}

//Тестируем, что установка функции для токенов цифр проходит нормально
TEST_F(TestTokenParser, Test3){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fi,nullptr);
    parser.SetDigitTokenCallback([](long int x){return x*x;});
    ASSERT_EQ(parser.fi(12),144);
}

//Тестируем, что установка функции для токенов строк проходит нормально
TEST_F(TestTokenParser, Test4){
    TokenParser parser = TokenParser();
    ASSERT_EQ(parser.fs,nullptr);
    parser.SetStringTokenCallback([](std::string x){return int(x.size());});
    ASSERT_EQ(parser.fs("abc"),3);
}

//Тестируем функцию парсинга
TEST_F(TestTokenParser, Test5){
    TokenParser parser = TokenParser();
    std::string line = "abc +412 2 abc 10 a";
    ASSERT_EQ(parser.Parse(line),"");

    parser.SetStartCallback([](){return std::string("Begin");});
    ASSERT_EQ(parser.Parse(line),"Begin ");

    parser.SetEndCallback([](){return std::string("End");});
    ASSERT_EQ(parser.Parse(line),"Begin End");

    parser.SetDigitTokenCallback([](long int x){return x*x;});
    ASSERT_EQ(parser.Parse(line),"Begin 2:4 10:100 End");

    parser.SetStringTokenCallback([](std::string x){return int(x.size());});
    ASSERT_EQ(parser.Parse(line),"Begin abc:3 +412:4 2:4 abc:3 10:100 a:1 End");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}