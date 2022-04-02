#include <iostream>

class Allocator
{
public:
    size_t maxSize;
    size_t offset;
    char* pointer;

    // Конструктор
    Allocator(){
        maxSize = 0;
        offset = 0;
        pointer = nullptr;
    }

    // Аллоцируется динамическая память указанного размера
    void makeAllocator(size_t maxSize){
        if (pointer != nullptr){
            delete [] pointer;
        }
        this->maxSize = maxSize;
        offset = 0;
        pointer = new char[maxSize];
    }

    // Возвращает указатель на блок запрошенного размера или nullptr
    char* alloc(size_t size){
        if ((offset + size > maxSize) || (size == 0)){
            return nullptr;
        }
        char *temp = pointer + offset;
        offset += size;
        return temp;
    }

    // Позволяет использовать свою память снова
    void reset(){
        offset = 0;
    }
    
    // Это деструктор
    ~Allocator(){
        delete [] pointer;
    }
};