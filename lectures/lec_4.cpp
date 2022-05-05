#include<iostream>


/*
 * program instructions are executed in registers
 * future instructions are kept in the l1 cache
 *
 * static variables are like global variables, but have limited scope!
 */

void stat_inc() // static increment
{
    static int i{0};
    std::cout << ++i << '\n';
}

class ClassA
{
public:
    static int i;
    static double get_pi()
    {
        return 3.1415926535;
    }
};

int ClassA::i{10}; // class static must be initialized outside of the class
// class static variables do not need to be instantiated as a result of this.

void init_str()
{
    static char tab[20];
    std::strcpy(tab, "Philip\0");
}

int static_demonstration()
{
    std::cout << "static increment method:\n";
    stat_inc();
    stat_inc();
    stat_inc();

    std::cout << "class method:\n";

    std::cout << ClassA::i << '\n';
    std::cout << ClassA::get_pi() << '\n';

    init_str();
    std::cout << "init_str doesn't work?\n";

    return 0;
}

class Order // abstract class? virtual class?
{
protected:
    int q;
public:
    Order(int q_): q{q_} {}

    void display() {std::cout << "Order with quantity " << q << '\n';}
    // non-pure virtual function here
};

class FOK : public Order
{
public:
    FOK(int q_): Order(q_) {} // call super class constructor.

    void display() {std::cout << "FOK Order with quantity " << q << '\n';}
};

class GTC: public Order
{
public:
    GTC(int q_): Order(q_) {}

    void display() {std::cout << "GTC Order with quantity " << q << '\n';}
};

class PNL
{
protected:
    double o;
    int n;
public:
    PNL(double o_, int n_): o{o_}, n{n_} {}
    void display() {std::cout << "PNL " << n << '\n';}
};

int order_again()
{
    FOK fok0(1), fok1(2), fok2(7);
    GTC gtc0(10), gtc1(25);
    Order* pointers[5]{&fok0, &gtc0, &gtc1, &fok1, &fok2};

    for (size_t i{0}; i<5; ++i)
    {
        pointers[i]->display(); // virtual allows the calling of the correct overridden class method
        // try deleting the virtual declaration in Order. Will only call Order::display()
    }

    std::cout << "static cast demo\n";
    fok0.display();
    Order ooo{static_cast<Order>(fok0)};
    ooo.display();

    PNL profit(0.0, 100);
    profit.display();

//    static_cast<Order>(profit); // does not work because these are different classes.

//    std::cout << "dynamic cast forces bad conversion into nullptr\n";
//    for (size_t i{0}; i<5; ++i)
//    {
//        dynamic_cast<PNL*>(pointers[i])->display();
//    }

    std::cout << "reinterpret cast forces conversion without nullptr\n";
    for (size_t i{0}; i<5; ++i)
    {
        reinterpret_cast<PNL*>(pointers[i])->display();
    }

    const int x{50};
    const int* y{&x};
//    *y = 60; // doesnt work

    int* z{const_cast<int*>(y)};
    *z = 60;

    std::cout << "const casted x using z to " << *z << '\n';

    return 0;
}

template<typename T>
T add(T a, T b) {return a+b;}

auto sub(auto a, auto b) {return a-b;}

template<typename T>
class ClassB
{
public:
    T add(T a, T b) {return a+b;}
};

template<typename T>
void swap(T* a,T* b)
{
    T temp{*a};
    *a = *b;
    *b = temp;
}

int templates_demo()
{
    std::cout << "\ntemplates\n";
    std::cout << "int add " << add(1, 2) << '\n';
    std::cout << "double add " << add(1.2, 2.5) << '\n';
    std::cout << "mixed add " << add<float>(1, 2.1) << '\n';

    std::cout << "\ntemplate using auto\n";
    std::cout << "mixed sub " << sub(1.2f, 2.3) << '\n';

    std::cout << "\ntemplate class\n";
    ClassB<float> cfloat;
    std::cout << "class float add " << cfloat.add(1.2f, 2.4f) << '\n';

    std::cout << "\ntemplate swap\n";
    int a{1}, b{100};
    std::cout << "before swap a=" << a << ", b=" << b << '\n';
    swap(&a,&b);
    std::cout << "after swap a=" << a << ", b=" << b << '\n';

    return 0;
}

int lec_4()
{
    static_demonstration();
    order_again();
    templates_demo();

    return 0;
}