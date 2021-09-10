#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <memory>
#include "Gameplay.h"
#include "./Observer.h"

class TextDisplay : public Observer
{
private:
    std::shared_ptr<Gameplay> subject;
    std::ostream &output;

public:
    TextDisplay(std::ostream &out, std::shared_ptr<Gameplay> game);
    ~TextDisplay();
    void notify() override;
    friend std::ostream &operator<<(std::ostream &out, TextDisplay const &t);
};

#endif