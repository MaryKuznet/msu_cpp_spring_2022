#include "BigInt.hpp"

BigInt::BigInt(string str)
{
    size_t i = 0;
    while (isblank(str[i])){
        i += 1;
    }
    if (str[i] == '-'){
        sign = false;
        i += 1;
    }
    while (str[i] == '0' && (i < str.size() - 1 && str[i + 1] != ' ')){
        i += 1;
    }
    string new_str;
    while (!isblank(str[i]) && i < str.size()){
        new_str.push_back(str[i]);
        i += 1;
    }
    len = new_str.size();
    digit = new int[len];
    for(i = 0; i < len; i++){
        digit[len - i - 1] = int(new_str[i]) - '0';
    }
}

BigInt::BigInt(size_t size)
{
    len = size;
    digit = new int[len];
    sign = true;
}

BigInt::BigInt(const BigInt &d)
{
    len = d.len;
    digit = new int[len];
    sign = d.sign;
    for(size_t i = 0; i < len; i++)
        digit[i] = d.digit[i];
}

BigInt::BigInt(BigInt &&d) noexcept
{
    len = d.len;
    digit = d.digit;
    sign = d.sign;

    d.len = 0;
    d.digit = nullptr;
    d.sign = true;
}

BigInt& BigInt::operator=(const BigInt& bigint)
{
    if (this == &bigint)
        return *this;
    len = bigint.len;
    for(size_t i; i < len; i++)
        digit[i] = bigint.digit[i];
    return *this;
}

std::ostream& operator<< (std::ostream &out, const BigInt &bigint){
    if (!bigint.sign){
        out << '-';
    }
    for(size_t i = 0; i < bigint.len; i++){
        out << bigint.digit[bigint.len - i - 1];
    }
    return out;
}

const BigInt operator+ (const BigInt& digit1, const BigInt& digit2)
{
    int *sum = nullptr;
    size_t len;
    digit1.len > digit2.len ? len = digit1.len + 1 : len = digit2.len + 1;
    bool sign = digit1.sign; 
    sum = new int[len];
    int c = 0;
    int sum_;
    for (size_t i = 0; i < len; i++)
    {
        if (digit1.len > i && digit2.len > i)
            sum_ = digit1.digit[i] + digit2.digit[i] + c;
        else if (digit1.len > i && digit2.len <= i)
                sum_ = digit1.digit[i] + c; 
        else if (digit1.len <= i && digit2.len > i)
                sum_ = digit2.digit[i] + c;
            else
                sum_ = c;
        c = 0;
        c = sum_ / 10;
        sum[i] = sum_ % 10;
    }
    size_t new_len;
    if (sum[len - 1] == 0)
        new_len = len - 1;
    else
        new_len = len;
    BigInt new_digit = BigInt(new_len);
    new_digit.sign = sign;
    for (size_t i = 0; i < new_len; i++)
    {
        new_digit.digit[i] = sum[i];
    }
    delete[] sum;
    return new_digit;
}

bool operator> (const BigInt& digit1, const BigInt& digit2)
{
    if (digit1.sign > digit2.sign)
        return true;
    else if (digit1.sign < digit2.sign)
        return false;

    bool flag = true;
    if (digit1.sign == 0)
        flag = false;
    
    if (digit1.len > digit2.len)
        return flag;
    else if (digit1.len < digit2.len)
        return !flag;
    
    for (size_t i = 0; i < digit1.len; i++){
        if (digit1.digit[digit1.len -1 - i] > digit2.digit[digit1.len -1 - i])
            return flag;
        else if (digit1.digit[digit1.len -1 - i] < digit2.digit[digit1.len -1 - i])
            return !flag;
    }
    return false;
}

bool operator>= (const BigInt& digit1, const BigInt& digit2)
{
    if (digit1.sign > digit2.sign)
        return true;
    else if (digit1.sign < digit2.sign)
        return false;
    
    bool flag = true;
    if (digit1.sign == 0)
        flag = false;
    
    if (digit1.len > digit2.len)
        return flag;
    else if (digit1.len < digit2.len)
        return !flag;
    
    for (size_t i = 0; i < digit1.len; i++){
        if (digit1.digit[digit1.len -1 - i] > digit2.digit[digit1.len -1 - i])
            return flag;
        else if (digit1.digit[digit1.len -1 - i] < digit2.digit[digit1.len -1 - i])
            return !flag;
    }
    return true;
}

bool operator< (const BigInt& digit1, const BigInt& digit2)
{
    if (digit1.sign < digit2.sign)
        return true;
    else if (digit1.sign > digit2.sign)
        return false;
    
    bool flag = true;
    if (digit1.sign == 0)
        flag = false;
    
    if (digit1.len < digit2.len)
        return flag;
    else if (digit1.len > digit2.len)
        return !flag;
    
    for (size_t i = 0; i < digit1.len; i++){
        if (digit1.digit[digit1.len -1 - i] < digit2.digit[digit1.len -1 - i])
            return flag;
        else if (digit1.digit[digit1.len -1 - i] > digit2.digit[digit1.len -1 - i])
            return !flag;
    }
    return false;
}

bool operator<= (const BigInt& digit1, const BigInt& digit2)
{
    if (digit1.sign < digit2.sign)
        return true;
    else if (digit1.sign > digit2.sign)
        return false;
    
    bool flag = true;
    if (digit1.sign == 0)
        flag = false;
    
    if (digit1.len < digit2.len)
        return flag;
    else if (digit1.len > digit2.len)
        return !flag;
    
    for (size_t i = 0; i < digit1.len; i++){
        if (digit1.digit[digit1.len -1 - i] < digit2.digit[digit1.len -1 - i])
            return flag;
        else if (digit1.digit[digit1.len -1 - i] > digit2.digit[digit1.len -1 - i])
            return !flag;
    }
    return true;
}

bool operator== (const BigInt& digit1, const BigInt& digit2)
{
    if (digit1.sign != digit2.sign)
        return false;
    
    if (digit1.len != digit2.len)
        return false;
    
    for (size_t i = 0; i < digit1.len; i++){
        if (digit1.digit[digit1.len -1 - i] != digit2.digit[digit1.len -1 - i])
            return false;
    }
    return true;
}

bool operator!= (const BigInt& digit1, const BigInt& digit2)
{
    if (digit1.sign != digit2.sign)
        return true;
    
    if (digit1.len != digit2.len)
        return true;
    
    for (size_t i = 0; i < digit1.len; i++){
        if (digit1.digit[digit1.len -1 - i] != digit2.digit[digit1.len -1 - i])
            return true;
    }
    return false;
}

const BigInt operator- (const BigInt& digit1){
    BigInt new_digit = digit1;
    new_digit.sign = !new_digit.sign;
    return new_digit;
}

const BigInt operator- (const BigInt& digit1, const BigInt& digit2)
{
    if ((digit1.sign == 1) && (digit2.sign == 0)){
        BigInt sub2 = -digit2;
        return digit1 + sub2;
    }
    else if ((digit1.sign == 0) && (digit2.sign == 1)){
        BigInt sub2 = -digit2;
        return digit1 + sub2;
    }
    bool sign = digit2 <= digit1;
    if (digit1.sign == 0 && digit2.sign == 0)
        sign = !sign;
    BigInt sub1 = sign ? digit1 : digit2;
    BigInt sub2 = sign ? digit2 : digit1;
    int *sub = nullptr;
    size_t len = sub1.len;
    sub = new int[len];
    int c = 0;
    int sub_;
    for (size_t i = 0; i < len; i++)
    {
        if (sub1.len > i && sub2.len > i)
            sub_ = sub1.digit[i] - sub2.digit[i] - c;
        else
            if (sub1.len > i && sub2.len <= i)
                sub_ = sub1.digit[i] - c; 
            else
                sub_ = - c;
        c = 0;
        if (sub_ < 0)
        {
            sub_ = 10 + sub_;
            c = 1;
        }
        sub[i] = sub_;
    }
    size_t new_len = len;
    while (new_len > 1 && sub[new_len - 1] == 0)
        new_len--;

    BigInt new_digit = BigInt(new_len);
    new_digit.sign = sign;
    for (size_t i = 0; i < new_len; i++)
    {
        new_digit.digit[i] = sub[i];
    }
    delete[] sub;
    return new_digit;
}

const BigInt operator* (const BigInt& digit1, const BigInt& digit2)
{
    if ((digit1.len == 0 && digit1.digit[0] == 0) || (digit2.len == 0 && digit2.digit[0] == 0))
        return BigInt("0");
    
    size_t len_ = digit1.len + digit2.len;
    int *vec =  new int[len_];
    for (size_t i = 0; i < len_; i++)
        vec[i] = 0;
    for (size_t i = 0; i < digit1.len;i++)
        for (size_t j = 0; j < digit2.len;j++){
            vec[i + j] += digit1.digit[i] * digit2.digit[j];
        }
    int *vec2 =  new int[len_];
    int s = 0;
    int t = 0;
    for (size_t i = 0; i < len_; i++)
    {
        s = t + vec[i];
        vec[i] = s % 10;
        t = s / 10;
        vec2[i] = vec[i];
    }
    size_t new_len = len_;
    for (size_t i = len_ - 1; i >= 1 && !vec[i];i--)
        --new_len;
    BigInt new_digit = BigInt(new_len);
    new_digit.sign = digit1.sign == digit2.sign;
    for (size_t i = 0; i < new_len; i++)
        new_digit.digit[i] = vec2[i];
    delete[] vec;
    delete[] vec2;
    return new_digit;
}

const BigInt operator* (const BigInt& digit1, const int32_t& digit2){
    return digit1 * BigInt(std::to_string(digit2));
}

const BigInt operator+ (const BigInt& digit1, const int32_t& digit2){
    return digit1 + BigInt(std::to_string(digit2));
}

const BigInt operator- (const BigInt& digit1, const int32_t& digit2){
    return digit1 - BigInt(std::to_string(digit2));
}

BigInt::~BigInt(){
    delete[] digit;
}