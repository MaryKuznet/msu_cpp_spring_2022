#include <iostream>

class Allocator
{
public:
    size_t maxSize;
    size_t offset;
    char* pointer;

    Allocator(){
        this->maxSize = 0;
        this->offset = 0;
        this->pointer = nullptr;
    }

    void makeAllocator(size_t maxSize){
        if (this->pointer != nullptr){
            delete this->pointer;
        }
        this->maxSize = maxSize;
        this->pointer = new char(maxSize);
    }

    char* alloc(size_t size){
        if (this->offset + size > this->maxSize){
            return nullptr;
        }
        char *temp = this->pointer + this->offset;
        this->offset += size;
        return temp;
    }

    void reset(){
        this->offset = 0;
    }
    
    // Это деструктор!
    ~Allocator(){
        delete this->pointer;
    }
};