#include <iostream>

class Allocator
{
public:
    size_t maxSize;
    size_t offset;
    char* pointer;

    // Конструктор
    Allocator(){
        this->maxSize = 0;
        this->offset = 0;
        this->pointer = nullptr;
    }

    // Аллоцируется динамическая память указанного размера
    void makeAllocator(size_t maxSize){
        if (this->pointer != nullptr){
            delete this->pointer;
        }
        this->maxSize = maxSize;
        this->offset = 0;
        this->pointer = new char[maxSize];
    }

    // Возвращает указатель на блок запрошенного размера или nullptr
    char* alloc(size_t size){
        if ((this->offset + size > this->maxSize) || (size == 0)){
            return nullptr;
        }
        char *temp = this->pointer + this->offset;
        this->offset += size;
        return temp;
    }

    // Позволяет использовать свою память снова
    void reset(){
        this->offset = 0;
    }
    
    // Это деструктор
    ~Allocator(){
        delete this->pointer;
    }
};