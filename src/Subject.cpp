#include "../include/Subject.h"
using namespace std;

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(shared_ptr<Observer> o)
{
    // create smart-pointer
    shared_ptr<Observer> ptr(o);
    observers.emplace_back(ptr);
}

void Subject::detach(shared_ptr<Observer> o)
{
    shared_ptr<Observer> ptr(o);
    for (auto it = observers.begin(); it != observers.end();)
    {
        if (*it == ptr)
        {
            observers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Subject::notifyObservers()
{
    for (auto ob : observers)
        ob->notify();
}
