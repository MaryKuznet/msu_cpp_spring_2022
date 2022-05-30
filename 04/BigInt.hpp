#include <iostream>
#include <string> 
using namespace std;

class BigInt{
public:
    bool sign = true;
    size_t len = 0;
    int *digit = nullptr;

    BigInt() = default;

    BigInt(string str);

    BigInt(size_t size);

    BigInt(const BigInt &d);

    BigInt(BigInt &&d) noexcept;

    BigInt& operator=(const BigInt& bigint);

    friend std::ostream& operator<< (std::ostream &out, const BigInt &digit);

    friend const BigInt operator+ (const BigInt& digit1, const BigInt& digit2);

    friend const BigInt operator- (const BigInt& digit1, const BigInt& digit2);

    friend bool operator> (const BigInt& digit1, const BigInt& digit2);

    friend bool operator>= (const BigInt& digit1, const BigInt& digit2);

    friend bool operator< (const BigInt& digit1, const BigInt& digit2);

    friend bool operator>= (const BigInt& digit1, const BigInt& digit2);

    friend bool operator== (const BigInt& digit1, const BigInt& digit2);

    friend bool operator!= (const BigInt& digit1, const BigInt& digit2);

    friend const BigInt operator* (const BigInt& digit1, const BigInt& digit2);

    friend const BigInt operator* (const BigInt& digit1, const int32_t& digit2);

    friend const BigInt operator+ (const BigInt& digit1, const int32_t& digit2);

    friend const BigInt operator- (const BigInt& digit1, const int32_t& digit2);

    ~BigInt();
};