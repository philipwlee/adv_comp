//#include <iostream>
//#include <string>
//#include <stdlib.h>
//#include <unordered_map>
//#include <cstring>
//
//using namespace std;
//enum ordertype {LIMIT, MARKET};
//
//
//class Order
//{
//private:
//    long timestamp{}; // unix time
//    bool is_buy{}; // buy or sell (false)
//    uint id{}, price{}, quantity{};
//    char venue[20]{}, symbol[20]{};
//    ordertype type{};
//public:
//    Order(long ts, bool ib, uint id_, uint pr, uint qt,
//          const char ven[20], const char sym[20], ordertype tp):
//            timestamp{ts}, is_buy{ib}, id{id_}, price{pr}, quantity{qt}, type{tp}
//    {
//        std::strcpy(venue, ven);
//        std::strcpy(symbol, sym);
//    }
//    char* getVenue() {return venue;}
//    char* getSymbol() {return symbol;}
//    uint getID() {return id;}
//    ordertype getOrderType() {return type;}
//    uint getQuantity() {return quantity;}
//    uint getPrice() {return price;}
//    bool is_valid() {return venue[0]!='\0';}
//
//    void setVenue(const char* venue_) {std::strcpy(venue, venue_);}
//    void setQuantity(uint quantity_) {quantity=quantity_;}
//};
//
//class OrderBook{
//private:
//    Order* order_bids[20]{}, * order_offers[20]{};
//    uint number_of_bids{0}, number_of_offers{0};
//public:
//    OrderBook() {}
//
//    bool add_order(long ts, bool ib, uint id_, uint pr, uint qt,
//                   const char ven[20], const char sym[20], ordertype tp)
//    {
//        Order* add_o{new Order{ts, ib, id_, pr, qt, ven, sym, tp}};
//        if (ib) // bid
//        {
//            if (order_bids[id_]!=NULL) {return false;} // id already occupied
//            else {order_bids[id_] = add_o; ++number_of_bids;}
//        }
//        else // offers
//        {
//            if (order_offers[id_]!=NULL) {return false;} // id already occupied
//            else {order_offers[id_] = add_o; ++number_of_offers;}
//        }
//        return true;
//    }
//    bool modify_order(bool ib, uint id_, uint qt)
//    {
//        if (ib)
//        {
//            if (order_bids[id_]!=NULL) order_bids[id_]->setQuantity(qt);
//            else return false;
//        }
//        else
//        {
//            if (order_offers[id_]!=NULL) order_offers[id_]->setQuantity(qt);
//            else return false;
//        }
//        return true;
//    }
//    bool remove_order(bool ib, uint id_)
//    {
//        if (ib) // bid
//        {
//            if (order_bids[id_]!=NULL)
//            {
//                delete order_bids[id_];
//                order_bids[id_]=NULL;
//                --number_of_bids;
//                return true;
//            }
//            else return false;
//        }
//        else // offer
//        {
//            if (order_offers[id_]!=NULL)
//            {
//                delete order_offers[id_];
//                order_offers[id_]=NULL;
//                --number_of_offers;
//                return true;
//            }
//            else return false;
//        }
//    }
//
//    //  ----------------------------------------------------------------
//    void clearBooks()
//    {
//        for(int k=0;k<20;k++)
//        {
//            if (order_bids[k]!=NULL)
//            {
//                delete order_bids[k];
//                order_bids[k]=NULL;
//                number_of_bids--;
//            }
//            if (order_offers[k]!=NULL)
//            {
//                delete order_offers[k];
//                order_offers[k]=NULL;
//                number_of_offers--;
//            }
//        }
//    }
//    Order* getOrderBids(const int a) {return order_bids[a];}
//    Order* getOrderOffers(const int a) {return order_offers[a];}
//    int getNumberOfBids() {return number_of_bids;}
//    int getNumberOfOffers() {return number_of_offers;}
//};
//
//int number_of_tests = 0;
//int number_of_pass = 0;
//// bool is_identical_array(int *array1, int *array2, int size1, int size2);
//
//#define TEST_FUNCTION(X,Y) {number_of_tests++; std::cout << "Test " << number_of_tests << ": "; if (X==Y) \
//                                {std::cout << " PASS" << std::endl;number_of_pass++;} \
//                            else\
//                                {std::cout << \
//                                " FAIL EXPECTED: " << \
//                                Y << " RECEIVED: " << X << std::endl;} \
//                            }
//#define TEST_NOT_EQUAL(X,Y) {number_of_tests++; std::cout <<  "Test " << number_of_tests << ": "; if (X!=Y) \
//                                {std::cout << " PASS" << std::endl;number_of_pass++;} \
//                            else\
//                                {std::cout << \
//                                " FAIL EXPECTED: " << \
//                                Y << " RECEIVED: " << X << std::endl;} \
//                            }
//
//#define TEST_STRING(X,Y) {number_of_tests++; std::cout <<  "Test " << number_of_tests << ": "; if (strcmp(X,Y)==0) \
//                                {std::cout << " PASS" << std::endl;number_of_pass++;} \
//                            else\
//                                {std::cout << \
//                                " FAIL EXPECTED: " << \
//                                Y << " RECEIVED: " << X << std::endl;} \
//                            }
//
//
//#define PRINT_RESULTS() {std::cout << "You succeeded to pass " << number_of_pass << "/" << number_of_tests;}
//
//// bool check_a(double *a);
//// bool check_b(double *a,int size);
//// bool check_c(double *a,int size);
//// bool check_c_result_3(double *a);
//
//bool is_identical_array(int *array1, int *array2, int size1, int size2)
//{
//    // If lengths of array are not equal means
//    // array are not equal
//    if (size1 != size2)
//        return false;
//    // Linearly compare elements
//    for (int i=0; i<size1; i++)
//        if (array1[i] != array2[i])
//            return false;
//    // If all elements were same.
//    return true;
//}
//
//
//bool check_a(double *a)
//{
//    return (a[0]==1 &&
//            a[1]==2 &&
//            a[2]==3 &&
//            a[3]==1 &&
//            a[4]==1 &&
//            a[5]==1 &&
//            a[6]==1 &&
//            a[7]==1 &&
//            a[8]==1);
//}
//
//bool check_b(double *a,int size)
//{
//    for (int k=0; k<size; k++)
//    {
//        if (a[k] != 1) return false;
//    }
//    return true;
//}
//
//bool check_c(double *a,int size)
//{
//    for (int k=0; k<size; k++)
//    {
//        if (a[k] != 0) return false;
//    }
//    return true;
//}
//
//bool check_c_result_3(double *a)
//{
//    return a[0]==4 && a[1]==5 && a[2]==6;
//}
//
//int phase_3_main() {
//    /* Create an order o1 on the stack with the following parameter
//     *
//     * (100,true,1,10,1000,"JPM","APPL",ordertype::LIMIT);
//     *
//     * */
//    Order o1(100,true,1,10,1000,"JPM","APPL",ordertype::LIMIT);
//
//    TEST_FUNCTION(o1.getID(),1);
//    TEST_FUNCTION(o1.getOrderType(),ordertype::LIMIT);
//    TEST_FUNCTION(o1.getPrice(),10);
//    TEST_FUNCTION(o1.getQuantity(),1000);
//    TEST_STRING(o1.getVenue(),"JPM");
//    TEST_STRING(o1.getSymbol(),"APPL");
//    TEST_FUNCTION(o1.is_valid(), true);
//    o1.setVenue("\0");
//    TEST_FUNCTION(o1.is_valid(), false);
//    o1.setVenue("BARX");
//    TEST_FUNCTION(o1.is_valid(), true);
//
//    // Create an order book on the stack
//
//    OrderBook b1;
//
//    // Add an order to the book
//
//    TEST_FUNCTION(b1.add_order(100,true,1,10,1000,"JPM","APPL",ordertype::LIMIT),true);
//    TEST_FUNCTION(b1.add_order(100,true,2,11,1000,"BARX","APPL",ordertype::MARKET),true);
//
//    TEST_STRING(b1.getOrderBids(1)->getVenue(), "JPM");
//    TEST_STRING(b1.getOrderBids(2)->getVenue(), "BARX");
//    TEST_FUNCTION(b1.getOrderBids(2)->getOrderType(), ordertype::MARKET);
//
//    TEST_FUNCTION(b1.add_order(100,false,4,11,1000,"BARX","APPL",ordertype::MARKET),true);
//    TEST_FUNCTION(b1.getOrderOffers(4)->getOrderType(), ordertype::MARKET);
//    TEST_FUNCTION(b1.add_order(100,false,4,11,1000,"BARX","APPL",ordertype::MARKET),false);
//
//    TEST_FUNCTION(b1.getNumberOfBids(),2);
//    TEST_FUNCTION(b1.getNumberOfOffers(),1);
//
//    //Reset the book
//    b1.clearBooks();
//
//    TEST_FUNCTION(b1.getNumberOfBids(),0);
//    TEST_FUNCTION(b1.getNumberOfOffers(),0);
//
//    int count_offer_null=0;
//    int count_bid_null=0;
//    for(int k=0;k<20;k++)
//    {
//        count_offer_null+=(b1.getOrderOffers(k)==NULL)?1:0;
//        count_bid_null+=(b1.getOrderBids(k)==NULL)?1:0;
//    }
//    TEST_FUNCTION(count_offer_null+count_bid_null,40);
//
//    for(int k=0;k<20;k++)
//    {
//        b1.add_order(100,false,k,50+k,1000-k*10,"BARX","APPL",ordertype::LIMIT);
//        b1.add_order(100,true,k,50-k,1000+k*100,"BARX","APPL",ordertype::LIMIT);
//    }
//
//    TEST_FUNCTION(b1.getNumberOfBids(),20);
//    TEST_FUNCTION(b1.getNumberOfOffers(),20);
//
//    unsigned int sum_quantity = 0;
//    for(int k=0;k<20;k++)
//    {
//        sum_quantity+=b1.getOrderOffers(k)->getQuantity();
//        sum_quantity+=b1.getOrderBids(k)->getQuantity();
//    }
//
//    TEST_FUNCTION(sum_quantity,57100);
//
//    for(int k=0;k<20;k++)
//    {
//        b1.modify_order(true,k,b1.getOrderBids(k)->getQuantity()-100);
//        b1.modify_order(false,k,b1.getOrderOffers(k)->getQuantity()-100);
//    }
//
//    sum_quantity = 0;
//    for(int k=0;k<20;k++)
//    {
//        sum_quantity+=b1.getOrderOffers(k)->getQuantity();
//        sum_quantity+=b1.getOrderBids(k)->getQuantity();
//    }
//
//
//    TEST_FUNCTION(sum_quantity,57100-100*40);
//
//    PRINT_RESULTS();
//    return 0;
//}