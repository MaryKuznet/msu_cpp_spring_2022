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
	ASSERT_EQ(A.offset, 0);
	ASSERT_NE(A.pointer, nullptr);
	
	// Повторно аллоцируем память
	A.makeAllocator(8);
	ASSERT_EQ(A.maxSize, 8);
	ASSERT_EQ(A.offset, 0);
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

	//Проверяем, что при запросе на блок 0 размера возвращает nullptr
	ptr3 = A.alloc(0);
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

// Проверки краевых условий и цепочек вызовов + тесты через возвращаемые указатели
TEST_F(TestAllocator, test4)
{
	//Проверки краевых условий
	Allocator A = Allocator();
	A.makeAllocator(1);
	ASSERT_EQ(A.alloc(1), A.pointer);
	ASSERT_EQ(A.alloc(1), nullptr);

	// Проверка цепочек вызовов
	A.makeAllocator(50);
	A.alloc(20);
	ASSERT_EQ(A.alloc(30), A.pointer + 20);
	ASSERT_EQ(A.alloc(1), nullptr);
	A.reset();
	ASSERT_EQ(A.alloc(50), A.pointer);
	ASSERT_EQ(A.alloc(1), nullptr);

	// Проверка цепочек вызовов
	A.makeAllocator(10);
	A.makeAllocator(8);
	ASSERT_EQ(A.alloc(10), nullptr);
	ASSERT_EQ(A.alloc(8), A.pointer);
	A.reset();
	ASSERT_EQ(A.alloc(4), A.pointer);
	ASSERT_EQ(A.alloc(3), A.pointer + 4);
	ASSERT_EQ(A.alloc(1), A.pointer + 7);
	ASSERT_EQ(A.alloc(1), nullptr);

	//Тесты через возвращаемые указатели
	A.makeAllocator(30);
	char* ptr1 = A.alloc(10);
	ASSERT_EQ(ptr1, A.pointer);
	char* ptr2 = A.alloc(10);
	ASSERT_EQ(ptr2, A.pointer + 10);
	ASSERT_EQ(ptr2 - ptr1, 10);
	char* ptr3 = A.alloc(10);
	ASSERT_EQ(ptr3, A.pointer + 20);
	ASSERT_EQ(ptr3 - ptr1, 20);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
