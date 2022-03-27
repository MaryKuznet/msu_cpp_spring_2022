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

TEST_F(TestAllocator, test1)
{
	Allocator A = Allocator();
	A.makeAllocator(10);
	ASSERT_EQ(A.maxSize, 10);
	ASSERT_NE(A.pointer, nullptr);
	A.makeAllocator(8);
	ASSERT_EQ(A.maxSize, 8);
	ASSERT_NE(A.pointer, nullptr);
}

TEST_F(TestAllocator, test2)
{
	Allocator A = Allocator();
	A.makeAllocator(10);

	char* ptr1 = A.alloc(12);
	ASSERT_EQ(ptr1, nullptr);

	ptr1 = A.alloc(4);
	ASSERT_EQ(ptr1, A.pointer);
	ASSERT_EQ(A.offset, 4);

	char* ptr2 = A.alloc(4);
	ASSERT_EQ(ptr2, A.pointer + 4);
	ASSERT_EQ(A.offset, 8);

	char* ptr3 = A.alloc(4);
	ASSERT_EQ(ptr3, nullptr);
}

TEST_F(TestAllocator, test3)
{
	Allocator A = Allocator();
	A.makeAllocator(10);
	char* ptr1 = A.alloc(4);
	ASSERT_EQ(ptr1, A.pointer);
	char* ptr2 = A.alloc(4);
	ASSERT_EQ(ptr2, A.pointer + 4);
	ASSERT_EQ(A.offset, 8);

	A.reset();
	ASSERT_EQ(A.offset, 0);

	char* ptr3 = A.alloc(4);
	ASSERT_EQ(ptr3, A.pointer);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
