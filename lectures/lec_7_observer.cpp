#include <iostream>
#include <set>

//template <class T, class U>
//class Subject;
//
//template <class T, class U>
//class Observer
//{
//private:
//    int i;
//public:
//    void update(Subject<T,U>* sub_);
//};
//
//template <class T, class U>
//class Subject
//{
//private:
//    Observer<T, U>* obs;
//public:
//    Subject(): obs=nullptr {}
//    void attach(Observer<T,U>* obs_) {static_cast<T>(this)->child_attach(obs_);}
//    void detach() {obs=nullptr;}
//};
//
//template <class T, class U>
//inline void Observer<T,U>::update(Subject<T,U>* sub_)
//{
//    static_cast<T>(this)->child_update(sub_);
//}
//
//template <class T, class U>
//class TradingStrategy: Observer<T,U>;
//
//template <class T, class U>
//class PositionManager: Subject<PositionManager, TradingStrategy<T,U>>
//{
//
//};

class Subject;

class Observer {
public:
    virtual ~Observer();
    virtual void Update (Subject* theChangedSubject)=0;
protected:
    Observer();
};

class Subject {
public:
    std::set<Observer*> *_observers;
    virtual ~Subject();
    virtual void Attach (Observer*);
    virtual void Detach (Observer*);
    virtual void Notify();
protected:
    Subject();
};

class PositionManager: public Subject
{
public:
    virtual void Attach(Observer* obs) {_observers->insert(obs);}
    virtual void Detach(Observer* obs) {_observers->erase(obs);}
};

class TradingStrategy: public Observer
{
public:
    virtual void Update(Subject* theChangedSubject)
    {
        int i{0};
    }
};

int lec_7_observer_main()
{

    return 0;
}

