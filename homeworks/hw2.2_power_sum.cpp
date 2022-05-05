#include<iostream>
#include<set>
#include<cmath>


int pow(int n, int exp)
{
    if (exp==0) return 1;
    else if (exp%2) return n * pow(n, exp/2) * pow(n, exp/2);
    else return pow(n, exp/2) * pow(n, exp/2);
}

int countPowerNumbers(int l, int r) {
    std::cout << l << ',' << r << '\n';

    std::set<int> pows{{0,1}}, pnums{};

    switch (l)
    {
        case 0: pnums.insert(0);
        case 1: pnums.insert(1);
    }
    if (l<=2 && r>=2) pnums.insert(2);

    for (int i{2}; i<sqrt(r)+1; ++i)
    {
        for (int ip{2}; pow(i, ip)<=r; ++ip)
        {
            int pp {pow(i, ip)};
            pows.insert(pp);

            std::set<int>::iterator b {pows.begin()}, e {pows.end()};
            for (; b!=e; ++b)
            {
                if ((*b + pp)>=l && (*b + pp)<=r) pnums.insert(*b + pp);
            }
        }
    }

    return pnums.size();
}