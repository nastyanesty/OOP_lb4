#ifndef OBSERVER_H
#define OBSERVER_H
#include <vector>

// Класс наблюдателя
class Observer{
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

// Класс наблюдаемого
class Observable{
private:
    std::vector<Observer*> observers;
public:
    void add_observer(Observer* observer);
    void notify_observers();
    virtual ~Observable() = default;
};

#endif //OBSERVER_H