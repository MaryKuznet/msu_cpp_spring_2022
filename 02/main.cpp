#include <iostream>
#include "Allocator.cpp"

// Рассматриваем на примерах, что все работает
int main(){
    // Создаем Allocator
    Allocator A = Allocator();

    // Выделяем память размера 8
    A.makeAllocator(8);

    // Выбираем оттуда блок размера 2
    char* ptr1 = A.alloc(2);
    ptr1 = (char*) "ab";
    std::cout<<ptr1<<std::endl;

    // Выбираем блок слишком большого размера 
    char* ptr2 = A.alloc(10);
    if (ptr2 == nullptr){
        std::cout<<"null"<<std::endl;
    }

    // Проверяем, что после reset память можно переиспользовать
    A.reset();
    char* ptr3 = A.alloc(7);
    ptr3 = (char*) "abcdefg";
    std::cout<<ptr3<<std::endl;
    
    return 0;
}