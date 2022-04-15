#include <iostream>

class Matrix{

    class ProxyRow
    {
    private:
        int *data_;
        size_t m;
    public:
        ProxyRow() = default;

        ProxyRow(size_t n);

        ~ProxyRow();

        int& operator[](size_t j);
    };

private:
    size_t n, m;
    ProxyRow *rows_;

public:
    Matrix(size_t n = 1, size_t m = 1);
    ~Matrix();

    size_t getRows();
    size_t getColumns();

    friend const Matrix operator+ (const Matrix& matr1, const Matrix& matr2);

    friend Matrix& operator*= (Matrix& matr1, int digit);

    friend std::ostream& operator<< (std::ostream &out, const Matrix &m);

    friend bool operator== (const Matrix& matr1, const Matrix& matr2);

    friend bool operator!= (const Matrix& matr1, const Matrix& matr2);

    ProxyRow& operator[](size_t i);
};