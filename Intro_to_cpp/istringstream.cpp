#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::istringstream stream("1 2 a b c 2");

    int i;
    char c;
    while (stream)
    {
        stream >> i;
        std::cout << (bool)(stream);
        //if (stream) std::cout << "int extraxcted " << i << "\n" ;
        //else {
        //    stream >> c;
        //    if (stream) std::cout << "char extraxcted " << c << "\n";
        //}
    }
}