#pragma once
#include <iostream>
#include <iterator>

template<class T>
class Allocator{
    public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count){
        pointer ptr = new value_type[count];
        return ptr;
    };

    void deallocate(pointer ptr){
        delete [] ptr;
    };
};


template <class T>
class Iterator: public std::iterator<std::forward_iterator_tag, T>{
private:
    T* ptr_;
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
public:
    explicit Iterator(pointer ptr): ptr_(ptr){}

    bool operator==(const Iterator<T>& other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T>& other) const
    {
        return !(*this == other);
    }

    bool operator< (const Iterator<T>& other) const noexcept{
        return ptr_ < other.ptr_;
    }

    bool operator> (const Iterator<T>& other) const noexcept{
        return ptr_ > other.ptr_;
    }

    bool operator<= (const Iterator<T>& other) const noexcept{
        return ptr_ <= other.ptr_;
    }

    bool operator>= (const Iterator<T>& other) const noexcept{
        return ptr_ >= other.ptr_;
    }

    // difference_type operator-(const Iterator<T>& other) const
    // {
    //     return std::distance(ptr_, other.ptr_);
    // }

    reference operator*() const{
        return *ptr_;
    }

    reference operator[] (int n) const{
        return ptr_[n];
    }

    Iterator& operator++() noexcept{
        ++ptr_;
        return *this;
    }

    Iterator& operator--() noexcept{
        --ptr_;
        return *this;
    }

    Iterator operator+ (int n) const noexcept{
        return Iterator(ptr_ + n);
    }

    Iterator operator- (int n) const noexcept{
        return Iterator(ptr_ - n);
    }
};


template<class T, class Alloc = Allocator<T>>
class Vector{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using allocator_type = Alloc;
    using pointer = T*;

public:
    Alloc alloc;
    pointer data;
    size_type size_;
    size_type len;

    explicit Vector(size_type count){
        len = count;
        size_ = 0;
        data = alloc.allocate(count);
    }

    ~Vector(){
        alloc.deallocate(data);
    }

    reference operator[] (size_type n){
        if (n >= size_)
            throw std::out_of_range("out of range");
        return data[n];
    }

    void push_back(const_reference value){
        if (size_ == len) {
            reserve(len + 1);
        }

        data[size_] = value;
        ++size_;
    }

    void emplace_back(T&& value){
        if (size_ == len) {
            reserve(len + 1);
        }

        data[size_] = std::move(value);
        ++size_;
    }

    void pop_back(){
        if (size_ > 0){
            --size_;
        } 
        else
            throw std::out_of_range("empty vector");
    }

    void clear(){
        size_ = 0;
    }

    void reserve(size_type new_len){
        pointer new_data = alloc.allocate(new_len);
        if (size_ > new_len)
            size_ = new_len;
        for (size_type i = 0; i < size_; i++) {
            new_data[i] = data[i];
        } 
        alloc.deallocate(data);
        data = new_data;
        len = new_len;
    }

    void resize(size_type new_size, const_reference value){
        if (new_size > size_){
            if (new_size > len){
                reserve(new_size);
            }
            for (size_type i = size_; i < new_size; i++) {
                data[i] = value;
            }
        }
        size_ = new_size;
    }

    size_type size() const noexcept{
        return size_;
    }

    size_type capacity() const noexcept{
        return len;
    }

    bool empty() const noexcept{
        return size_ == 0;
    }

    Iterator<T> begin() const noexcept{
        return Iterator(data);
    }

    Iterator<T> end() const noexcept{
        return Iterator(data + size_);
    }

    std::reverse_iterator<Iterator<T>> rbegin() const noexcept{
        return std::reverse_iterator<Iterator<T>>(end());
    }

    std::reverse_iterator<Iterator<T>> rend() const noexcept{
        return std::reverse_iterator<Iterator<T>>(begin());
    }
};