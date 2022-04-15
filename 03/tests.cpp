#include <iostream>
#include "Matrix.cpp"
#include <gtest/gtest.h>

class TestMatrix : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

//Проверка получения количества строк(rows) и столбцов(columns)
TEST_F(TestMatrix, Test1){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);
}

// Проверка получения конкретного элемента и ошибки при неправильном индексе
TEST_F(TestMatrix, Test2){
    Matrix m(2, 3);
    m[1][1] = 1;
    ASSERT_EQ(m[1][1], 1);
    ASSERT_EQ(m[0][0], 0);

    double x = m[1][1];
    ASSERT_EQ(x, 1);

    x = m[0][1];
    ASSERT_EQ(x, 0);

    Matrix m2(2, 4);
    ASSERT_THROW(x = m2[3][3], out_of_range);
    ASSERT_NO_THROW(x = m2[1][1]);
}

// Проверка умножения *=
TEST_F(TestMatrix, Test3){
    Matrix m(2, 3);
    m[1][1] = 1;
    m[0][0] = 2;
    
    Matrix m2(2, 3);
    m2[1][1] = 3;
    m2[0][0] = 6;

    m *= 3;

    ASSERT_EQ(m, m2);

    m *= 0;
    Matrix m3(2, 3);
    ASSERT_EQ(m, m3);
}

// Проверка сложения
TEST_F(TestMatrix, Test4){
    Matrix m(2, 3);
    m[1][1] = 2;
    m[0][0] = 2;
    
    Matrix m2(2, 3);
    m2[1][1] = -1;
    m2[0][0] = 6;
    m2[1][2] = -6;

    Matrix m3(2, 3);
    m3[1][1] = 1;
    m3[0][0] = 8;
    m3[1][2] = -6;

    ASSERT_EQ(m + m2, m3);

}

// Проверка сравнений на равенство и неравенство
TEST_F(TestMatrix, Test5){
    Matrix m(2, 3);
    m[1][1] = 2;
    m[0][0] = 2;
    
    Matrix m2(2, 3);
    m2[1][1] = 2;
    m2[0][0] = 2;
    m2[1][2] = -6;

    Matrix m3(2, 3);
    m3[1][1] = 2;
    m3[0][0] = 2;
    m3[1][2] = -6;

    assert(m2 == m3);
    assert(m != m2);
    ASSERT_FALSE(m == m2);
    ASSERT_FALSE(m2 != m3);

}

// Проверка вывода матрицы в поток (ostream)
TEST_F(TestMatrix, Test6){
    testing::internal::CaptureStdout();
    Matrix m(2, 3);
    m[1][1] = 2;
    m[0][0] = 1;
    cout << m << endl;
    string out = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(out.c_str(), " 1 0 0\n 0 2 0\n\n");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}