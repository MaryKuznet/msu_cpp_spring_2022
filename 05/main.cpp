#include "Serializer.cpp"
#include <iostream>

int main()
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    Error e = deserializer.load(y);
    if (e == Error::CorruptedArchive) std::cout << "error" << std::endl;
    else std::cout << "no error" << std::endl;

    std::cout << y.a << " " << y.b << " " << y.c << std::endl;
}
