#include <iostream>

template <class T>
class Singleton
{
private:
    inline static T* sing{nullptr};
public:
    // Singleton(): sing{nullptr} {}
    void display_log()
    {
        std::cout << "I am a singleton" << std::endl;
    }
    static T& getInstance()
    {
        if (sing==nullptr) {sing=new T{};}
        return *sing;
    }
};

class Logger:public Singleton<Logger>
{
    friend class Singleton<Logger>;
private:
    Logger(){};
    ~Logger(){};
public:
    void display_log(std::string logtext){
        std::cout << logtext << std::endl;
        static_cast<Singleton<Logger> *>(this)->display_log();
    }
};

Logger * ff1()
{
    Logger::getInstance().display_log("display log from f1");
    return &Logger::getInstance();
}

Logger * ff2()
{
    Logger::getInstance().display_log("display log from f2");
    return &Logger::getInstance();
}

int singleton_main(void)
{
    Logger::getInstance().display_log("Try to make it work");      // use Logger
    std::cout << (ff1()==ff2()) << std::endl;
    return 0;
}
