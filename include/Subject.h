#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <memory>
#include "Observer.h"

class Subject
{
    std::vector<std::shared_ptr<Observer>> observers;

public:
    Subject();
    void attach(std::shared_ptr<Observer> o);
    void detach(std::shared_ptr<Observer> o);
    void notifyObservers();
    virtual ~Subject() = 0;
};

#endif
