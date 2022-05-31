#include "PoolTreads.hpp"

using namespace std;

struct A {};

int foo(const A&) {return 1;}

int main()
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    int a = task1.get();
    cout << a << endl;

    auto task2 = pool.exec([]() { return 1; });
    int b = task2.get();
    cout << b << endl;
}
