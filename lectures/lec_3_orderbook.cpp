#include<iostream>
#include<string>
#include"exchange.h"

class OrderBook
{
private:
    int* bids{ nullptr }, * asks{ nullptr };
    int nb_orders{};
public:
    OrderBook(int number_of_orders): nb_orders{number_of_orders} // Constructor
    {
        bids = new int[nb_orders] {}; // initialized to 0
        asks = new int[nb_orders] {}; // these are on the heap
    }
    OrderBook(const OrderBook &ob)
    {
        nb_orders = ob.nb_orders;
        bids = new int[nb_orders] {};
        asks = new int[nb_orders] {};
        for (int _{0}; _<nb_orders; _++)
        {
            bids[_] = ob.bids[_];
            asks[_] = ob.asks[_];
        }
    }
    OrderBook operator+(const OrderBook &right)
    {
        OrderBook temp((*this).nb_orders + right.nb_orders);
        for (int _{0}; _<(*this).nb_orders; _++)
        {
            // although bids, asks are private, they can be accessed here because
            // this code block is within the scope of the class.
            temp.bids[_] = (*this).bids[_];
            temp.asks[_] = (*this).asks[_];
        }
        for (int _{0}; _<right.nb_orders; _++)
        {
            temp.bids[(*this).nb_orders + _] = right.bids[_];
            temp.asks[(*this).nb_orders + _] = right.asks[_];
        }
        return temp;
    }
    OrderBook& operator++() // no argument passed -> prefix ++ob
    {
        for (int _{0}; _<nb_orders; _++) {++bids[_]; ++asks[_];}
        return *this;
    }
    OrderBook operator++(int) // when an argument is passed -> postfix ob++
    {
        // 1. creates copy, 2. increments *this, 3. returns copy
        const OrderBook copy{(*this)};
        for (int _{0}; _<nb_orders; _++) {bids[_]++; asks[_]++;}
        return copy;
    }
    void set_bids(int idx, int value) {bids[idx] = value;}
    void set_asks(int idx, int value) {asks[idx] = value;}
    void initialize(int offset)
    {
        for (int _{0}; _<nb_orders; _++)
        {
            bids[_] = asks[_] = _ + offset;
        }
    }
    friend std::ostream &operator << (std::ostream &os, const OrderBook &obj);
};

std::ostream& operator << (std::ostream& os, const OrderBook &obj)
{
    std::string temp;
    os << "Bids: ";
    for (int _{0}; _<obj.nb_orders; _++) os << obj.bids[_] << ',';
    os << "\nAsks: ";
    for (int _{0}; _<obj.nb_orders; _++)os << obj.asks[_] << ',';
    os << '\n';
    return os;
}

int orderbook_main()
{
    OrderBook ob1{5}; // created on the stack (orderbook_main scope)
    ob1.initialize(10);
    std::cout << ob1;
    std::cout << ob1++;
    std::cout << ++ob1;
    std::cout << ob1;

    OrderBook ob2(3); // uses different, newly allocated order books
    ob2.initialize(20);

    OrderBook ob3{ob1+ob2};
    std::cout << ob3;

    return 0;
}
