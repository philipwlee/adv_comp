#include <iostream>

/*
 * Observer template
 *
 * Subject -notifies-> Observer
 * Exchange -> Orderbook
 * PositionManager -> TradingStrategy
 *
 */


// Factory Design pattern
class Parser
{
public:
    Parser()=default;
    void echo()
    {
        std::cout << "ECHO\n";
    }
};

class BARXFixParser: public Parser
{
public:
    BARXFixParser(bool isFix){}
};

class JPMXFixParser: public Parser
{
public:
    JPMXFixParser(int c) {}
};

class Factory
{
public:
    static Parser* createInstance(std::string venue)
    {
        if      (venue=="JPMX") {return new JPMXFixParser{2};}
        else if (venue=="BARX") {return new BARXFixParser{false};}
        else {return new Parser{};}
    }
};

void factory_main()
{
    Parser* par{Factory::createInstance("JPMX")};
    par->echo();
}

/*
 *
 */

int lec_7_main()
{
    std::cout << "Lecture 7 main\n";

    factory_main();

    return 0;
}
