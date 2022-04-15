#include "Matrix.hpp"
using namespace std;

Matrix::Matrix(size_t _n, size_t _m): n(_n), m(_m) {
    rows_ = new ProxyRow[n];
    for(size_t i = 0; i < n; i++){
        rows_[i] = ProxyRow(m);
    }
}

Matrix::~Matrix(){
    delete[] rows_;
}

size_t Matrix::getColumns(){
    return m;
}

size_t Matrix::getRows(){
    return n;
}

std::ostream& operator<< (std::ostream &out, const Matrix &matr){
    for(size_t i = 0; i < matr.n; i++){
        for(size_t j = 0; j < matr.m; j++){
            out << " " <<matr.rows_[i][j];
        }
        out << "\n";
    }
    return out;
}

const Matrix operator+ (const Matrix& matr1, const Matrix& matr2){
    Matrix new_m(matr1.n, matr2.m);
    for(size_t i = 0; i < matr1.n; i++){
        for(size_t j = 0; j < matr1.m; j++){
            new_m.rows_[i][j] = matr1.rows_[i][j] + matr2.rows_[i][j];
        }
    }
    return new_m;
}

Matrix& operator*= (Matrix& matr1, int digit){
    for(size_t i = 0; i < matr1.n; i++){
        for(size_t j = 0; j < matr1.m; j++){
            matr1.rows_[i][j] = matr1.rows_[i][j] * digit;
        }
    }
    return matr1;
}

bool operator== (const Matrix& matr1, const Matrix& matr2){
    bool res = true;
    for(size_t i = 0; i < matr1.n; i++){
        for(size_t j = 0; j < matr1.m; j++){
            res = matr1.rows_[i][j] == matr2.rows_[i][j];
            if (res == false){
                return res;
            }
        }
    }
    return res;
}

bool operator!= (const Matrix& matr1, const Matrix& matr2){
    bool res = false;
    for(size_t i = 0; i < matr1.n; i++){
        for(size_t j = 0; j < matr1.m; j++){
            res = matr1.rows_[i][j] == matr2.rows_[i][j];
            if (res == false){
                return true;
            }
        }
    }
    return false;
}

Matrix::ProxyRow::ProxyRow(size_t _m) : m(_m) {
    data_ = new int [m];
    for (size_t j = 0; j < m; j++) {
        data_[j] = 0;
    }
}

Matrix::ProxyRow::~ProxyRow() {
}

int& Matrix::ProxyRow::operator[](size_t j)
{
    if (j >= m) {
        throw out_of_range("");
    }
    return data_[j];
}

Matrix::ProxyRow& Matrix::operator[](size_t i)
{
    if (i >= n) {
        throw out_of_range("");
    }
    return rows_[i];
}
