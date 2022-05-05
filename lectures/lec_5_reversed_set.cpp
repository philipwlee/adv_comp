#include<iostream>
#include<set>
#include<functional>


int rev_set_main()
{
    std::set<int, std::greater<> > s;
    for (int i{1}; i<16; ++i) s.insert(i);

    std::cout << "Printing\n";
    for (auto itr: s) std::cout << itr << '\n';

    std::cout << "\nReversing\n";
    for (auto itr{s.rbegin()}; itr!=s.rend(); ++itr) std::cout << *itr << '\n';
    return 0;
}