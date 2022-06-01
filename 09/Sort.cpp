#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <cmath>
#include <algorithm>
#include <string>

int file_processing(std::ifstream &f){
    f.seekg(0, f.end);
    // size_t len = f.tellg() / sizeof(uint64_t);
    f.seekg(0, f.beg);

    uint64_t* buf = new uint64_t[1000*1024];
    int k = 0;
    while(!f.eof()) {
        std::cout<<"delim"<<std::endl;
        f.read(reinterpret_cast<char *>(buf), 1000*1024 * sizeof(uint64_t));

        size_t read_sz = f.gcount() / sizeof(uint64_t);

        std::thread t1([buf, read_sz]() {
            std::sort(buf, buf + read_sz / 2);
        });

        std::thread t2([buf, read_sz]() {
            std::sort(buf + read_sz / 2, buf + read_sz);
        });
        t1.join();
        t2.join();

        std::ofstream f1(std::to_string(k), std::ios::binary);
        ++k;
        std::ofstream f2(std::to_string(k), std::ios::binary);
        ++k;

        f1.write(reinterpret_cast<const char *>(buf), sizeof(uint64_t) * read_sz / 2);
        f2.write(reinterpret_cast<const char *>(buf + read_sz / 2), sizeof(uint64_t) * read_sz / 2);
        f1.close();
        f2.close();

        std::cout<<"podelili"<<std::endl;
        int g;
        std::cin>>g;
    }
    f.close();
    delete[] buf;
    return k;
}

void merge(int k){
    uint64_t* buf = new uint64_t[1000*1024];
    for (int i = 0; i < k; ++i) {
        std::ifstream f1(std::to_string(i), std::ios::binary);
        std::ifstream f2(std::to_string(i + 1), std::ios::binary);

        int g;

        std::cout<< i <<std::endl;
        std::cin>>g;

        uint64_t digit;

        f1.read(reinterpret_cast<char *>(&digit), sizeof(uint64_t));
        f2.seekg(0, f2.end);
        size_t len = f2.tellg() / sizeof(uint64_t);
        f2.seekg(0, f2.beg);
        f2.read(reinterpret_cast<char *>(buf), len * sizeof(uint64_t));
        f2.close();

        std::ofstream f_new(std::to_string(i + 1), std::ios::binary);

        size_t j = 0;
        while ((j < len)&&(!f1.eof())){
            if (digit >= buf[j]) {
                f_new.write(reinterpret_cast<const char *>(&buf[j]), sizeof(uint64_t));
                ++j;
            }
            if (digit <= buf[j]) {
                f_new.write(reinterpret_cast<const char *>(&digit), sizeof(uint64_t));
                f1.read(reinterpret_cast<char *>(&digit), sizeof(uint64_t));
            }
        }

        if (f1.eof())
            f_new.write(reinterpret_cast<const char *>(&buf[j]), sizeof(uint64_t) * (len - j));
        while (!f1.eof()) {
            f_new.write(reinterpret_cast<const char *>(&digit), sizeof(uint64_t));
            f1.read(reinterpret_cast<char *>(&digit), sizeof(uint64_t));
        }
        f1.close();
        remove(std::to_string(i).c_str());
        f_new.close();       
    };
    delete[] buf;
}

int main(){
    std::ifstream file_for_sort("in.bin", std::ios::in | std::ios::binary);
    int amount = file_processing(file_for_sort);
    merge(amount);
    return 0;
}