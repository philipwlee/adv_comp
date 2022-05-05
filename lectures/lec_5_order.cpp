#include<iostream>


class L5Order
{
public:
    L5Order()
    {
        std::cout << "Order Construtor Called\n";
    }
    ~L5Order()
    {
        std::cout << "Order Destructor Called\n";
    }
    void print()
    {
        std::cout << "JKAHKJDJKJDKAS\n";
    }
};

//template<class T>
class MSP
{
private:
    static int ref_count;
    L5Order* ptr;
public:
    MSP(L5Order* ptr_): ptr{ptr_}
    {
        std::cout << "***Smart ptr construct\n";
        ++MSP::ref_count;
    }
    ~MSP()
    {
        std::cout << "***Smart ptr " << MSP::ref_count << " destruct\n";
        --MSP::ref_count;
        if (!MSP::ref_count)
        {
            delete ptr;
            ptr = nullptr;
        }
    }
    L5Order* get_ptr()
    {
        return ptr;
    }
};

int MSP::ref_count = 0;

int lec_5_order_main()
{
    std::cout << "Lec 5 Order\n";

    {
        std::shared_ptr<L5Order> point{ new L5Order() };
        std::weak_ptr<L5Order> oink { point };

        point->print();
    }

    return 0;
}