#include <iostream>
#include "Allocator.cpp"

int main(){
    Allocator A = Allocator();
    A.makeAllocator(8);
    char* ptr1 = A.alloc(2);
    ptr1 = (char*) "ab";
    std::cout<<ptr1<<std::endl;
    char* ptr2 = A.alloc(10);
    if (ptr2 == nullptr){
        std::cout<<"null"<<std::endl;
    }
    A.reset();
    char* ptr3 = A.alloc(7);
    ptr3 = (char*) "abcdefg";
    std::cout<<ptr3<<std::endl;
    return 0;
}