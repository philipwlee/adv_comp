#ifndef ADV_COMP_EXCHANGE_H
#define ADV_COMP_EXCHANGE_H

class Order
{
private:
    double price;
    int quantity;
public:
    // C++ constructor has the same name as the class
    Order(double p, int q);
    Order(const Order &proto);
    Order& operator=(const Order &proto);
    Order operator+(const Order &right);
    ~Order();

    void set_price(double sprice);
    void set_quantity(int squantity);
    double get_price();
    int get_quantity();
};

#endif //ADV_COMP_EXCHANGE_H
