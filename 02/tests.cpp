#include <iostream>
#include "Allocator.cpp"
#include <gtest/gtest.h>

class TestAllocator : public ::testing::Test{
    protected:
	void SetUp()
	{
	}
	void TearDown()
	{
	}
	Allocator A;
};

// Тестируем метод makeAllocator
TEST_F(TestAllocator, test1)
{
	Allocator A = Allocator();
	// Аллоцируем память размера 10
	A.makeAllocator(10);
	ASSERT_EQ(A.maxSize, 10);
	ASSERT_NE(A.pointer, nullptr);
	// Повторно аллоцируем память
	A.makeAllocator(8);
	ASSERT_EQ(A.maxSize, 8);
	ASSERT_NE(A.pointer, nullptr);
}

// Тестируем метод alloc
TEST_F(TestAllocator, test2)
{
	Allocator A = Allocator();
	A.makeAllocator(10);

	// Проверяем, что возвращает nullptr, так как места недостаточно
	char* ptr1 = A.alloc(12);
	ASSERT_EQ(ptr1, nullptr);

	// Проверяем, что возвращает указатель на блок запрошенного размера
	ptr1 = A.alloc(4);
	ASSERT_EQ(ptr1, A.pointer);
	ASSERT_EQ(A.offset, 4);

	// Работает и при повторном вызове
	char* ptr2 = A.alloc(4);
	ASSERT_EQ(ptr2, A.pointer + 4);
	ASSERT_EQ(A.offset, 8);

	// Снова проверяем, что раз места теперь недостаточно, то возвращает nullptr
	char* ptr3 = A.alloc(4);
	ASSERT_EQ(ptr3, nullptr);
}

// Тестируем метод reset
TEST_F(TestAllocator, test3)
{
	Allocator A = Allocator();
	A.makeAllocator(10);
	char* ptr1 = A.alloc(4);
	ASSERT_EQ(ptr1, A.pointer);
	char* ptr2 = A.alloc(4);
	ASSERT_EQ(ptr2, A.pointer + 4);
	ASSERT_EQ(A.offset, 8);

	//После вызова reset offset снова указывает на начало
	A.reset();
	ASSERT_EQ(A.offset, 0);

	//После вызова reset аллокатор позволяет использовать свою память снова
	char* ptr3 = A.alloc(4);
	ASSERT_EQ(ptr3, A.pointer);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
