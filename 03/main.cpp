#include "Matrix.cpp"

int main(){
    Matrix m(2, 2);
    m[0][0] = 1;
    cout << m << endl;
    m *= 2;
    cout << m << endl;

    cout << m[1][1] << endl;

    m[1][1] = 5;
    cout << m << endl;
}