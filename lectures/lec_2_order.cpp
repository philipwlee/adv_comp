#include<iostream>
#include<string>

// GLOBAL
int ninst{0};


// struct vs class: default struct public; default class private
class Order
{
protected:
    double price {};
    int quantity {};
public:
    // C++ constructor has the same name as the class
    Order(double p, int q): price{p}, quantity{q} {++ninst;}
    Order(const Order &proto) // Copy constructor (overloaded constructor that takes
                              // an object of the same type as the argument
    { // must pass by reference otherwise an infinite recursion occurs
        std::cout << "Copy constructor \n";
    }
    Order& operator=(const Order &proto) // overload the = operator
    {
        (*this).quantity = proto.quantity;
        (*this).price = proto.price;
        return *this;
    }
    Order operator+(const Order &right)
    {
        Order sum((*this).price+right.price,
                  (*this).quantity+right.quantity);
        return sum;
        // sum is not destroyed; the compiler is optimized to keep sum and not create a copy.
    }
    ~Order()
    {
        // if Order is instantiated on the stack, it is destroyed at the end of the scope
        // If Order is allocated to the heap... ???
        --ninst;
        std::cout << "Base Order destructor called here.\n";
    }

    void set_price(double sprice) {price=sprice;}
    void set_quantity(int squantity) {quantity=squantity;}
    double get_price() {return price;}
    int get_quantity() {return quantity;}

    std::string get_features()
    {
        return "Order - Price: " + std::to_string(price) + " Qty: " + std::to_string(quantity);
    }
};

/* FOKOrder inherits from Order
 * protected variables can be accessed by the derived class
 * public can be accessed everywhere
 * private cannot be accessed outside of the class
 */
class FOKOrder : public Order // <- public can be changed to private, protected
        //       ^^^^^^ can be changed
{
public:
    FOKOrder(double p, int q):Order(p, q) {}
    ~FOKOrder()
    {
        std::cout << "Child FOK destructor called here. Then, we call base destructor...\n";
    }

    virtual std::string get_features()
    //^^^^^ virtual helps remind that this function is also in the base class
    {
        return "FOKOrder - Price: " + std::to_string(price) + " Qty: " + std::to_string(quantity);
    }
};

int order_main()
{
    std::cout << "Before instantiating, there are" << ninst << "orders.\n";
    {
        Order a(54.12, 200);
        std::cout << ninst << " orders instantiated.\nOrder object instantiated:\n";
        std::cout << a.get_price() << ", " << a.get_quantity() << '\n';

        std::cout << a.get_features() << '\n';

        FOKOrder f(54.14, 100);
        std::cout << ninst << " orders instantiated.\n";
        std::cout << f.get_features() << '\n';

        // calling parent get_features method
        Order* b{&f};
        std::cout << (*b).get_features() << '\n';
        // b isn't deleted because it is a pointer, not an object
        // therefore, it doesn't change the number of orders instantiated.
        std::cout << ninst << " orders instantiated.\n";
    }

    std::cout << "After the block goes out of scope, there are " << ninst << " orders.\n";

    return 0;
}

//int order_main_old()
//{
//    Order a(54.12, 200);
//    std::cout << "Order object instantiated:\n";
//    std::cout << a.get_price() << ", " << a.get_quantity() << '\n';
//
//    a.set_quantity(100);
//    a.set_price(54.68);
//    std::cout << "Order object modified using setters:\n";
//    std::cout << a.get_price() << ", " << a.get_quantity() << '\n';
//
//    std::cout << "Order object instantiated on the HEAP:\n";
//    Order* b = new Order(123.44, 500); // allocate to the heap.
//
//    std::cout << "Part1\n";
//    delete(b); // if delete() is not called, Order b may remain in the memory (memory leak)
//    std::cout << "Part2\n";
//    std::cout << "Part3\n";
//
//    Order copy_a(a); // Copy Constructor:
//
//    std::cout << "Order object instantiated by copy:\n";
//    std::cout << copy_a.get_price() << ", " << copy_a.get_quantity() << '\n';
//
//    Order order1(10.12, 100);
//    Order order2(56.99, 800);
//    Order order3(99.64, 100);
//
//    std::cout << "Instantiated Objects order1 and 2\n";
//    std::cout << order1.get_price() << ", " << order1.get_quantity() << '\n';
//    std::cout << order2.get_price() << ", " << order2.get_quantity() << '\n';
//    std::cout << order3.get_price() << ", " << order3.get_quantity() << '\n';
//
//    order3=order2=order1;
//
//    std::cout << "Called assignment order3=order2=order1\n";
//    std::cout << order1.get_price() << ", " << order1.get_quantity() << '\n';
//    std::cout << order2.get_price() << ", " << order2.get_quantity() << '\n';
//    std::cout << order3.get_price() << ", " << order3.get_quantity() << '\n';
//
//    Order order4 {order1+order2};
//    // NOTE the absence of the destructor
//    std::cout << order4.get_price() << ", " << order4.get_quantity() << '\n';
//    return 0;
//}