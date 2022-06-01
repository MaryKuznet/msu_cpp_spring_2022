#include <iostream>
#include "Sort.cpp"
#include <gtest/gtest.h>

class TestSort: public::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

TEST_F(TestSort, Test1){
    std::ofstream file("in.bin", std::ios::binary);
    uint64_t n = 11;
    for (size_t i = 0; i < 10; ++i) {
        file.write(reinterpret_cast<const char*>(&n), sizeof(uint64_t));
        --n;
    }
    file.close();

    std::ifstream file_for_sort("in.bin", std::ios::in | std::ios::binary);
    int amount = file_processing(file_for_sort);
    merge(amount);

    std::ifstream f(std::to_string(amount), std::ios::binary);
    uint64_t digit1;
    uint64_t digit2;
    size_t len = f.tellg() / sizeof(uint64_t);
    f.read(reinterpret_cast<char *>(&digit1), sizeof(uint64_t));
    for(size_t i = 1; i < len; ++i){
        f.read(reinterpret_cast<char *>(&digit2), sizeof(uint64_t));
        ASSERT_TRUE(digit1 <= digit2);
        digit1 = digit2;
    }
}