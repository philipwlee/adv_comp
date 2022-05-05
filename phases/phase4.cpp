#include <iostream>
#include <string.h>
#include <stdlib.h>

// Change this to false when you are ready to submit
#define DEBUG true

enum ordertype {LIMIT, MARKET};

class Order{
private:
    long timestamp; // epoch time: the number of seconds that have elapsed since 00:00:00 Coordinated Universal Time (UTC), Thursday, 1 January 1970,.
    bool is_buy; // buy or sell
    unsigned int id; // order id – unique identifier
    unsigned int price;
    unsigned int quantity;
    char venue[20]; // company name where this order comes from
    char symbol[20];
    ordertype type;
public:
    Order(long timestamp_,
          bool is_buy_,
          unsigned int id_,
          unsigned int price_,
          unsigned int quantity_,
          const char * venue_,
          const char * symbol_,
          ordertype type_)
    {
        timestamp=timestamp_;
        id=id_;
        price=price_;
        quantity=quantity_;
        strcpy(venue,venue_);
        type=type_;
        strcpy(symbol,symbol_);
    }

    char * getVenue()
    {
        return venue;
    }

    char * getSymbol()
    {
        return symbol;
    }

    unsigned int getID()
    {
        return id;
    }

    ordertype getOrderType()
    {
        return type;
    }

    unsigned int getQuantity()
    {
        return quantity;
    }

    unsigned int getPrice()
    {
        return price;
    }

    bool is_valid()
    {
        return (quantity>=0 && price >=0 && (&venue!=NULL && venue[0]!='\0'));
    }

    void setVenue(const char * venue_)
    {
        strcpy(venue,venue_);
    }

    void setQuantity(unsigned int quantity_)
    {
        quantity=quantity_;
    }

    virtual unsigned int getOutstandingQuantity() {return 0;}
};

class OpenOrder : public Order
{
public:
    OpenOrder(long timestamp_,
              bool is_buy_,
              unsigned int id_,
              unsigned int price_,
              unsigned int quantity_,
              const char * venue_,
              const char * symbol_,
              ordertype type_):

            Order(timestamp_, is_buy_, id_, price_,
                  quantity_, venue_, symbol_, type_) {}

    unsigned int getOutstandingQuantity() {return getQuantity();}
};

class ClosedOrder : public Order
{
public:
    ClosedOrder(long timestamp_,
                bool is_buy_,
                unsigned int id_,
                unsigned int price_,
                unsigned int quantity_,
                const char * venue_,
                const char * symbol_,
                ordertype type_):

            Order(timestamp_, is_buy_, id_, price_,
                  quantity_, venue_, symbol_, type_) {}

    unsigned int getOutstandingQuantity() {return 0;}
};

class VectorOrders{
private:
    Order** orders;
    unsigned int capacity;
    unsigned int current_new_order_offset;
public:
    VectorOrders(unsigned int capacity_): capacity{capacity_}
    {
        orders = new Order*[capacity];
        current_new_order_offset = 0;
    }
    VectorOrders(const VectorOrders &vo)
    {
//        if (DEBUG) std::cout << "COPY CONSTRUCTOR!\n";
        capacity = vo.capacity;
        current_new_order_offset = vo.current_new_order_offset;

        orders = new Order*[capacity];
        for (int i{0}; i<current_new_order_offset; ++i)
        {
//            std::cout << "copy order " << i << '\n';
            orders[i] = vo.orders[i];
        }
    }

    Order **get_order_list() const
    {
        return orders;
    }

    bool double_list_orders_size()
    {
        Order** new_orders{new Order*[capacity*2]};
        for (int i{0}; i<capacity; ++i) new_orders[i] = orders[i];
        delete orders;
        orders = new_orders;
        capacity*=2;
        return true;
        // You will use this function
        // To reallocate an the array and doublinc its size
    }

    bool add_order(Order *o){
//        if (DEBUG) std::cout << "Adding order\n";
        if (current_new_order_offset>=capacity-1) double_list_orders_size();
        // check for duplicate IDs
        int i{0};
        while (orders[i]!=NULL)
        {
            if (orders[i]->getID()==o->getID()) return false;
            ++i;
        }

        orders[current_new_order_offset] = o;
        ++current_new_order_offset;
        return true;
    }

    unsigned int get_size()
    {
        return current_new_order_offset;
    }

    unsigned int get_capacity()
    {
        return capacity;
    }

    void clear()
    {
        for (unsigned int i{0}; i<current_new_order_offset; ++i)
        {
            delete orders[i];
            orders[i] = nullptr;
        }
        current_new_order_offset = 0;
    }

    bool delete_order(unsigned int id)
    {
        int i{0};
        bool not_found{true}, shifting{false};
        while (orders[i]!=nullptr)
        {
            if (not_found & (orders[i]->getID()==id))
            {
//                delete orders[i];
                orders[i] = orders[i+1];
                shifting=true;
                not_found=false;
                --current_new_order_offset;
            }
            else if (shifting & (orders[i]!=nullptr))
            {
                orders[i] = orders[i+1];
            }
            ++i;
        }
        if (not_found) return false;
        else return true;
    }

    int get_total_volume()
    {
        int tot_vol{0};
        for (int i{0}; i<current_new_order_offset; ++i) tot_vol+=orders[i]->getQuantity();
        return tot_vol;
    }

    unsigned int get_total_outstanding_volume()
    {
        unsigned int tot_vol{0};
        for (int i{0}; i<current_new_order_offset; ++i) tot_vol+=orders[i]->getOutstandingQuantity();
        return tot_vol;
    }

    void dump_list_orders();
};

int number_of_tests_p4 = 0;
int number_of_pass_p4 = 0;

#define TEST_FUNCTION(X,Y) {number_of_tests_p4++; if (DEBUG) {std::cout << "line:" << __LINE__ << " ";}; if (X==Y) \
                                {std::cout << "PASS" << std::endl; number_of_pass_p4++;} \
                            else\
                                {std::cout << \
                                " FAIL EXPECTED: " << \
                                Y << " RECEIVED: " << X << std::endl;} \
                            }

#define TEST_STRING(X,Y) {number_of_tests_p4++; if (DEBUG) {std::cout << "line:" << __LINE__ << " ";}; if (strcmp(X,Y)==0) \
                                {std::cout << "PASS" << std::endl;number_of_pass_p4++;} \
                            else\
                                {std::cout << \
                                " FAIL EXPECTED: " << \
                                Y << " RECEIVED: " << X << std::endl;} \
                            }


#define PRINT_RESULTS() {std::cout << "You succeeded to pass " << number_of_pass_p4 << "/" << number_of_tests_p4 << std::endl;}


int phase4_main() {
    Order o1(100,true,1,10,1000,"JPMX","EURUSD",ordertype::LIMIT);

    TEST_FUNCTION(o1.getID(),1);
    TEST_FUNCTION(o1.getOrderType(),ordertype::LIMIT);
    TEST_FUNCTION(o1.getPrice(),10);
    TEST_FUNCTION(o1.getQuantity(),1000);
    TEST_STRING(o1.getVenue(),"JPMX");
    TEST_STRING(o1.getSymbol(),"EURUSD");
    TEST_FUNCTION(o1.is_valid(), true);
    o1.setVenue("\0");
    TEST_FUNCTION(o1.is_valid(), false);
    o1.setVenue("BARX");
    TEST_FUNCTION(o1.is_valid(), true);

    Order *o2= new Order(101,true,2,11,1000,"BARX","EURUSD",ordertype::LIMIT);
    Order *o3= new Order(102,true,3,12,1500,"EBS","EURUSD",ordertype::LIMIT);
    Order *o4= new Order(103,true,4,13,500,"EBS","EURUSD",ordertype::LIMIT);
    Order *o5= new Order(104,false,5,14,500,"EBS","EURUSD",ordertype::LIMIT);

    VectorOrders list_orders_eurusd(20);
    list_orders_eurusd.add_order(o2);
    list_orders_eurusd.add_order(o3);
    list_orders_eurusd.add_order(o4);
    list_orders_eurusd.add_order(o5);

    TEST_FUNCTION(list_orders_eurusd.get_size(), 4);

    list_orders_eurusd.clear();

    TEST_FUNCTION(list_orders_eurusd.get_size(), 0);
    TEST_FUNCTION(list_orders_eurusd.get_capacity(), 20);

    for(int k=0;k<20;k++)
    {
        list_orders_eurusd.add_order(new Order(104+k,true,5+k,14+k,500+k,"EBS","EURUSD",ordertype::LIMIT));
    }

    TEST_FUNCTION(list_orders_eurusd.get_capacity(), 40);
    TEST_FUNCTION(list_orders_eurusd.get_size(), 20);

    TEST_FUNCTION(list_orders_eurusd.get_total_volume(), 10190);

    for(int k=20;k<40;k++)
    {
        list_orders_eurusd.add_order(new Order(104+k,true,5+k,14+k,500+k,"EBS","EURUSD",ordertype::LIMIT));
    }

    TEST_FUNCTION(list_orders_eurusd.get_capacity(), 80);
    TEST_FUNCTION(list_orders_eurusd.get_size(), 40);

    TEST_FUNCTION(list_orders_eurusd.get_total_volume(), 20780);

    for(int k=20;k<40;k++)
    {
        list_orders_eurusd.delete_order(5+k);
    }

    TEST_FUNCTION(list_orders_eurusd.get_total_volume(), 10190);

    Order * verif_null_order=NULL;
    for(int k=20;k<40;k++)
    {
        verif_null_order=list_orders_eurusd.get_order_list()[k];
        if (verif_null_order!=NULL)
            break;
    }
    TEST_FUNCTION(verif_null_order, (Order *)NULL);

    TEST_FUNCTION(list_orders_eurusd.get_order_list()[16]->getQuantity(),516);
    list_orders_eurusd.delete_order(16);
    TEST_FUNCTION(list_orders_eurusd.get_order_list()[16]->getQuantity(),517);
    TEST_FUNCTION(list_orders_eurusd.get_order_list()[19],(Order *)NULL);

    VectorOrders l2(list_orders_eurusd);

    TEST_FUNCTION(list_orders_eurusd.get_total_volume(),9679);
    TEST_FUNCTION(l2.get_total_volume(),9679);

    TEST_FUNCTION(l2.delete_order(4),false);
    TEST_FUNCTION(l2.delete_order(7),true);


    TEST_FUNCTION(l2.get_total_volume(),9177);
    TEST_FUNCTION(list_orders_eurusd.get_total_volume(),9679);

    list_orders_eurusd.clear();

    for(int k=0;k<20;k++)
    {
        list_orders_eurusd.add_order(new ClosedOrder(104+k,true,5+k,14+k,500+k,"EBS","EURUSD",ordertype::LIMIT));
    }

    TEST_FUNCTION(list_orders_eurusd.get_total_outstanding_volume(),0);

    list_orders_eurusd.clear();

    for(int k=0;k<20;k++)
    {
        list_orders_eurusd.add_order(new OpenOrder(104+k,true,5+k,14+k,500+k,"EBS","EURUSD",ordertype::LIMIT));
    }

    TEST_FUNCTION(list_orders_eurusd.get_total_outstanding_volume(),10190);


    PRINT_RESULTS();
    if (DEBUG) {
        std::cout << "Be sure to set DEBUG to false at top of file before submitting." << std::endl;
    }
    return 0;
}