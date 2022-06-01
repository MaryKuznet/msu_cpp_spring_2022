#include "Vector.cpp"
#include <gtest/gtest.h>

class TestVector : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

// Тестируем c типом long int: push_back, pop_back, empty, clear, size, capacity, operator[]
TEST_F(TestVector, Test1){
    size_t capacity_ = 3;
    Vector<long int> v = Vector<long int>(capacity_);

    assert(v.empty());

    v.push_back(100);
    v.push_back(200);

    EXPECT_THROW(v[2], std::out_of_range);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), 3);

    v.push_back(300);
    v.push_back(400);

    ASSERT_EQ(v[0], 100);
    ASSERT_EQ(v[1], 200);
    ASSERT_EQ(v[2], 300);
    ASSERT_EQ(v[3], 400);

    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.capacity(), 4);

    v.pop_back();

    EXPECT_THROW(v[3], std::out_of_range);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 4);

    ASSERT_FALSE(v.empty());

    v.clear();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 4);
    EXPECT_THROW(v.pop_back(), std::out_of_range);

    assert(v.empty());

}

// Тестируем c типом int: emplace_back, reserve, resize, size, capacity, operator[]
TEST_F(TestVector, Test2){
    Vector<int> v = Vector<int>(5);

    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 5);

    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);

    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);
    EXPECT_THROW(v[4], std::out_of_range);

    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.capacity(), 5);

    v.reserve(3);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    EXPECT_THROW(v[3], std::out_of_range);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);

    v.reserve(5);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 5);

    v.resize(2, 1);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    EXPECT_THROW(v[2], std::out_of_range);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), 5);

    v.resize(4, 3);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 3);
    EXPECT_THROW(v[4], std::out_of_range);
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.capacity(), 5);

}

// Тестируем c типом string
TEST_F(TestVector, Test3){
    Vector<std::string> v = Vector<std::string>(4);

    v.push_back("a");
    v.push_back("b");
    v.push_back("c");
    v.push_back("d");

    ASSERT_EQ(v[0], "a");
    ASSERT_EQ(v[1], "b");
    ASSERT_EQ(v[2], "c");
    ASSERT_EQ(v[3], "d");

}

// Тестируем begin, rbegin, end, rend
TEST_F(TestVector, Test4){
    Vector<int> v = Vector<int>(10);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
    ASSERT_EQ(v[3], 4);

    int k = 1;
    for (Iterator it = v.begin(); it < v.end(); ++it){
        ASSERT_EQ(*it, k);
        ++k;
    }

    for (Iterator it = v.end() - 1; it >= v.begin(); --it){
        --k;
        ASSERT_EQ(*it, k);
    }

    for (auto it = v.rend() - 1; it != v.rbegin() - 1; --it){
        ASSERT_EQ(*it, k);
        ++k;
    }

    for (auto it = v.rbegin(); it != v.rend(); ++it){
        --k;
        ASSERT_EQ(*it, k);
    }
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
