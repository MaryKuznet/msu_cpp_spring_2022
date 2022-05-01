#include <iostream>
#include "Serializer.cpp"
#include <gtest/gtest.h>

class TestSerializer : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

// Проверяем что сериализатор правильно переводит в строку наши структуры
TEST_F(TestSerializer, Test1){
    // Проверка для одной структуры
    Data x { 1, true, 2 };
    std::stringstream stream;
    std::string str;

    Serializer serializer(stream);
    serializer.save(x);
    getline(stream, str);
    ASSERT_EQ(str, "1 true 2 ");

    // Проверка для нескольких структур
    Data y { 3, false, 0 };
    Data z { 5, false, 4 };
    std::stringstream stream_2;
    std::string str_2;

    Serializer serializer_2(stream_2);
    serializer_2.save(x);
    serializer_2.save(y);
    serializer_2.save(z);
    getline(stream_2, str_2);
    ASSERT_EQ(str_2, "1 true 2 3 false 0 5 false 4 ");

    // Проверка для структуры другого типа
    Data_2 x_2 {true, 2, false, 3};
    std::stringstream stream_3;
    std::string str_3;

    Serializer serializer_3(stream_3);
    serializer_3.save(x_2);
    getline(stream_3, str_3);
    ASSERT_EQ(str_3, "true 2 false 3 ");
}

// Проверяем что десерилизатор правильно расшифровывает наши структуры
TEST_F(TestSerializer, Test2){
    // Проверка для одной структуры
    Data x { 1, true, 2 };
    Data y;
    std::stringstream stream;
    stream << 1 << " true " << 2 << " ";

    Deserializer deserializer(stream);
    deserializer.load(y);
    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);

    // Проверка для нескольких структур
    std::stringstream stream_2;
    Data z { 5, false, 4 };
    Data g { 3, false, 0 };
    Data x_1;
    Data x_2;

    stream_2 << 5 << " false " << 4 << " " << 3 << " false " << 0 << " ";
    
    Deserializer deserializer_2(stream_2);
    deserializer_2.load(x_1);
    Error err = deserializer_2.load(x_2);

    ASSERT_EQ(z.a, x_1.a);
    ASSERT_EQ(z.b, x_1.b);
    ASSERT_EQ(z.c, x_1.c);

    ASSERT_EQ(g.a, x_2.a);
    ASSERT_EQ(g.b, x_2.b);
    ASSERT_EQ(g.c, x_2.c);

    ASSERT_EQ(err, Error::NoError);

    // Проверка для структуры другого типа
    Data_2 other {true, 2, false, 3};
    Data_2 other_2;
    std::stringstream stream_6;
    stream_6 << "true "<< 2 << " false " << 3 << " ";

    Deserializer deserializer_6(stream_6);
    deserializer_6.load(other_2);
    ASSERT_EQ(other.a, other_2.a);
    ASSERT_EQ(other.b, other_2.b);
    ASSERT_EQ(other.c, other_2.c);
    ASSERT_EQ(other.d, other_2.d);

    // Проверка чтоу нас ошибка, если мы пытаемся десерилизовать в неправильную структуру
    Data h;
    std::stringstream stream_3;

    stream_3 << 5 << " " << 4 << " true ";
    Deserializer deserializer_3(stream_3);
    err = deserializer_3.load(h);
    ASSERT_EQ(err, Error::CorruptedArchive);

    // Проверка что у нас ошибка, если мы пытаемся десерилизовать неполную структуру
    std::stringstream stream_4;

    stream_4 << 5 << " true ";
    Deserializer deserializer_4(stream_4);
    err = deserializer_4.load(h);
    ASSERT_EQ(err, Error::CorruptedArchive);

    // Проверка что у нас ошибка, если мы пытаемся десерилизовать со значением больше uint64_t
    std::stringstream stream_5;

    stream_5 << 5 << " true " << "18446744073709551616 ";
    Deserializer deserializer_5(stream_5);
    err = deserializer_5.load(h);
    ASSERT_EQ(err, Error::CorruptedArchive);
}

// Проверяем работу серилизатора и десирилизатора вместе
TEST_F(TestSerializer, Test3){
    // Для первой структуры
    Data x { 1, true, 2 };
    Data y { 60, false, 10 };
    Data x_2;
    Data y_2;

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);
    serializer.save(y);

    Deserializer deserializer(stream);
    Error err = deserializer.load(x_2);
    assert(err == Error::NoError);
    err = deserializer.load(y_2);
    assert(err == Error::NoError);

    ASSERT_EQ(x.a, x_2.a);
    ASSERT_EQ(x.b, x_2.b);
    ASSERT_EQ(x.c, x_2.c);

    ASSERT_EQ(y.a, y_2.a);
    ASSERT_EQ(y.b, y_2.b);
    ASSERT_EQ(y.c, y_2.c);

    // Для второй структуры
    Data_2 z {true, 2, false, 3};
    Data_2 z_2;
    std::stringstream stream_2;

    Serializer serializer_2(stream_2);
    serializer_2.save(z);

    Deserializer deserializer_2(stream_2);
    deserializer_2.load(z_2);
    ASSERT_EQ(z_2.a, z_2.a);
    ASSERT_EQ(z.b, z_2.b);
    ASSERT_EQ(z.c, z_2.c);
    ASSERT_EQ(z.d, z_2.d);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}