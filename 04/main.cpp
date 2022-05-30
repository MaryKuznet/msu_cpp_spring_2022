#include "BigInt.cpp"

int main(){
    BigInt c ( " -13 " );
    BigInt b ( "12" );

    cout << b << endl;
    cout << c << endl;
    string s = std::to_string(12);
    cout << BigInt(s) << endl;
    int32_t a = -13;
    BigInt d = BigInt(std::to_string(a));
    cout << d.len << endl;
    cout << c * 12  << endl;
    cout << b * d << endl;
}