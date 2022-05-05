#include <iostream>


template<class T>
class Order{
protected:
    int q;
public:
    Order(int n):q(n){}
    void display(){
        T::child_display();
        std::cout << q << '\n';
    }
};

class FOK : public Order<FOK>{
public:
    FOK(int n):Order(n){}
    static void child_display(){
        std::cout << "FOK:";
    }

};

class GTC : public Order<GTC>{
public:
    GTC(int n):Order(n){}
    static void child_display(){
        std::cout << "GTC:";
    }

};

int curious_main(){

    FOK f0(10), f1(15);
    GTC g0(3), g1(7);

    f0.display();
    f1.display();
    g0.display();
    g1.display();

    return 0;
};
