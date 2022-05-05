#include<iostream>

bool isPossible(int a, int b, int c, int d, bool pow)
{
    std::cout << a << ',' << b << ',' << c << ',' << d << '\n';
    if ((a==c) && (b==d)) return true;
    else if ((a>c) || (b>d)) return false;
    else return (isPossible(a, a+b, c, d, true) || isPossible(a+b, b, c, d, true));
}

std::string isPossible(int a, int b, int c, int d) {
    bool sol {isPossible(a, b, c, d, true)};
    if (sol) return "Yes";
    else return "No";
}