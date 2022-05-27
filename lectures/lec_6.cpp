#include <iostream>
#include <vector>


void decltype_examples()
{
    decltype(2) my_guess{10};
    decltype(my_guess) new_inty{21};

    std::cout << "DECLTYPES\n";
    std::cout << "decltype infers the type of the variable that is passed so therefore my_guess=" << my_guess << '\n';
    std::cout << "same with new_inty=" << new_inty << "\n\n";
}

template <typename T>
T add_example(T a, T b) {return a+b;}

int add_ptr_func(int a, int (*fct_ptr)(int, int)) {return fct_ptr(a, a);}
//                     ^ dereferences the function pointer

void function_pointer_examples()
{
    std::cout << "FUNCTION POINTERS\n";
    std::cout << "add function 5+10=" << add_example(5,10) << '\n';
    std::cout << "double function 5,5=" << add_ptr_func(5, add_example) << '\n';
    std::cout << "same as lambda function 5,5=" <<
        add_ptr_func(5, [] (int a, int b) -> int {return a+b;}) << '\n';

    int c{10};
    std::cout << "capture example 1,3,c=" << [c] (int a, int b) -> int {return a+b+c;}(1,3) << '\n';
    //                                        ^ assigns c to the return value of the lambda
    //                                          [a] (int a)-> int{return a+1}(1);
    //                                          functionally equiv to
    //                                          a+=1;
    std::cout << "c=" << c << '\n';
    std::cout << '\n';
}

void range_base()
{
    std::cout << "Range Base\n";
    std::vector<int> vec{0,1,2,3,4,5,6,7,8,9};

    for (auto i: vec) {std::cout << i << ", ";} // this copies all elements into i
    std::cout << "\na faster example using references:\n";
    for (auto& i: vec) {i*=2; std::cout << i << ", ";} // this makes i reference
    std::cout << '\n';
}

// DO NOT COPY

class NonCopy
{
public:
    NonCopy()=default;                  // more legible
    NonCopy(const NonCopy&)=delete;     // prevent copying
    NonCopy operator=(NonCopy)=delete;  // prevent assignment
};

void no_copy()
{
    NonCopy nc;
//    NonCopy ab{nc}; // this ain't allowed unless there exists a copy constructor
}

int lec_6_main()
{
    std::cout << "Lecture 6\n\n";

    decltype_examples();
    function_pointer_examples();
    range_base();
    no_copy();

    return 0;
}