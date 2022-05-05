#include<iostream>


template<typename T>
class myvector
{
private:
    size_t size, idx;
    T* arr;
public:
    myvector(size_t size_=32): size{size_}
    {
        arr = new T[size]{};
        idx = 0;
    }

    void expand(size_t size_)
    {
        std::cout << "Expanding... allocated size was " << size << ". Now it is " << 2*size << '\n';
        size = 2*size_;
        T* temp = new T[size]{};
        for (int i{}; i<size_; ++i) {temp[i] = arr[i];}
        delete arr;
        arr = temp;
    }

    void push_back(T elem)
    {
        if (idx==size) {expand(size);}
        arr[idx] = elem;
        ++idx;
    }

    void print()
    {
        for (int i{0}; i<idx-1; ++i) {std::cout << arr[i] << ", ";}
        std::cout << arr[idx-1] << '\n';
    }

    size_t len() {return idx;}
    size_t alloc_size() {return size;}
};

int vector_main()
{
    myvector<int> mv{2};
    mv.push_back(0);
    mv.push_back(1);
    mv.print();
    mv.push_back(2);
    mv.push_back(3);
    mv.print();
    std::cout << "Current length is " << mv.len() << '\n';

    mv.push_back(4);
    mv.print();
    std::cout << "Current length is " << mv.len() << '\n';
    std::cout << "Current allocated size is " << mv.alloc_size() << '\n';

    for (int i{5}; i<32; ++i) {mv.push_back(i);}
    std::cout << "Current length is " << mv.len() << '\n';
    std::cout << "Current allocated size is " << mv.alloc_size() << '\n';
    return 0;
}