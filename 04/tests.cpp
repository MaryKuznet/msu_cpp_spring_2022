#include <iostream>
#include "BigInt.cpp"
#include <gtest/gtest.h>

class TestBigInt : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

//Проверка операций сравнения
TEST_F(TestBigInt, Test1){
    BigInt a = BigInt("123456");
    BigInt b = BigInt("123456");
    BigInt c = BigInt("-123456");
    BigInt d = BigInt("12345");
    BigInt e = BigInt("-12345");
    BigInt g = BigInt("0");

    assert(a == b);
    ASSERT_FALSE(a == d);
    ASSERT_FALSE(a == c);

    assert(a != d);
    ASSERT_FALSE(a != b);
    assert(a != c);

    assert(a > d);
    assert(a > c);
    assert(e > c);
    ASSERT_FALSE(a > b);
    ASSERT_FALSE(c > a);

    assert(a >= d);
    assert(a >= c);
    assert(e >= c);
    assert(a >= b);
    ASSERT_FALSE(c >= a);

    assert(d < a);
    assert(c < a);
    assert(c < e);
    ASSERT_FALSE(b < a);
    ASSERT_FALSE(a < c);

    assert(d <= a);
    assert(c <= a);
    assert(c <= e);
    assert(b <= a);
    ASSERT_FALSE(a <= c);
}

// Проверка операций сложения и вычитания
TEST_F(TestBigInt, Test2){
    BigInt a = BigInt("123456");
    BigInt b = BigInt("123456");
    BigInt c = BigInt("-123456");
    BigInt d = BigInt("12345");
    BigInt e = BigInt("-12345");
    BigInt g = BigInt("0");
    int32_t f = 123456;

    ASSERT_EQ(a + b, BigInt("246912"));
    ASSERT_EQ(a + g, a);
    ASSERT_EQ(c + e, BigInt("-135801"));
    ASSERT_EQ(a + 123456, BigInt("246912"));
    ASSERT_EQ(a + 0, a);
    ASSERT_EQ(a + f, BigInt("246912"));

    ASSERT_EQ(a - g, a);
    ASSERT_EQ(a - b, g);
    ASSERT_EQ(a - d, BigInt("111111"));
    ASSERT_EQ(d - a, BigInt("-111111"));
    ASSERT_EQ(e - d, BigInt("-24690"));
    ASSERT_EQ(d - e, BigInt("24690"));
    ASSERT_EQ(a - 0, a);
    ASSERT_EQ(a - 123456, g);
    ASSERT_EQ(a - f, g);
}

// Проверка умножения
TEST_F(TestBigInt, Test3){
    BigInt a = BigInt("123456");
    BigInt b = BigInt("123456");
    BigInt c = BigInt("-123456");
    BigInt d = BigInt("15241383936");
    BigInt e = BigInt("-12345");
    BigInt g = BigInt("0");

    ASSERT_EQ(a * b, BigInt("15241383936"));
    ASSERT_EQ(a * c, BigInt("-15241383936"));
    ASSERT_EQ(c * a, BigInt("-15241383936"));
    ASSERT_EQ(c * c, BigInt("15241383936"));
    ASSERT_EQ(a * g, BigInt("0"));
    ASSERT_EQ(a * 0, BigInt("0"));
    ASSERT_EQ(a * 123456, BigInt("15241383936"));
}

// Проверка вывода в поток (ostream)
TEST_F(TestBigInt, Test4){
    testing::internal::CaptureStdout();
    BigInt a = BigInt("  12345678901234567890 ");
    BigInt b = BigInt("  -123456 ");

    cout << a << endl;
    string out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "12345678901234567890\n");

    testing::internal::CaptureStdout();
    cout << b << endl;
    out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), "-123456\n");
}

// Проверка копирующего и перемещающего конструктора/оператора
TEST_F(TestBigInt, Test5){
    BigInt a = BigInt("123456");
    BigInt b = a;

    ASSERT_EQ(b, a);
    BigInt c = [](BigInt x){BigInt c = -x; return c;}(a);
    ASSERT_EQ(c, -a);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
