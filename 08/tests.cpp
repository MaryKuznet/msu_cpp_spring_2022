#include <iostream>
#include "PoolTreads.hpp"
#include <gtest/gtest.h>
#include <cmath>

class TestPoolTreads : public ::testing::Test{
    protected:
	void SetUp(){}
	void TearDown(){}
};

//Через id потоков проверяем как распределяются задачи для пула размером 2
TEST_F(TestPoolTreads, Test1){

    ThreadPool pool(2);

    auto task1 = pool.exec([](){pow(234567, 100);});
    task1.get();

    auto task2 = pool.exec([](){pow(3, 100);});
    task2.get();

    auto task3 = pool.exec([](){pow(2, 100);});
    task3.get();

    ASSERT_EQ(pool.ids[0], pool.threads[0].get_id());
    ASSERT_EQ(pool.ids[1], pool.threads[1].get_id());
    ASSERT_EQ(pool.ids[2], pool.threads[0].get_id());
}

//Через id потоков проверяем как распределяются задачи для пула размером 3
TEST_F(TestPoolTreads, Test2){

    ThreadPool pool(3);

    auto task1 = pool.exec([](){pow(234567, 100);});
    task1.get();

    auto task2 = pool.exec([](){pow(234568, 100);});
    task2.get();

    auto task3 = pool.exec([](){pow(234569, 100);});
    task3.get();

    ASSERT_EQ(pool.ids[0], pool.threads[0].get_id());
    ASSERT_EQ(pool.ids[1], pool.threads[1].get_id());
    ASSERT_EQ(pool.ids[2], pool.threads[2].get_id());
}

// Проверяем, что возвращаются верные значения
TEST_F(TestPoolTreads, Test3){

    struct A {int a;};
    ThreadPool pool(8);

    A a1 = A();
    a1.a = 1;
    A a2 = A();
    a2.a = 2;

    auto task1 = pool.exec([](const A& b){return 2*b.a;}, a1);
    int res1 = task1.get();

    auto task2 = pool.exec([](const A& b){return 2*b.a;}, a2);;
    int res2 = task2.get();

    ASSERT_EQ(res1, 2*a1.a);
    ASSERT_EQ(res2, 2*a2.a);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}