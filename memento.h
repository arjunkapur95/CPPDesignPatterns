#ifndef MEMENTO_H
#define MEMENTO_H

#include "state.h"


class memento
{
private:
    // accessible only to Memento and Originator
    friend  class  Originator;
    memento (State *state){this->state = state;}//Originator can create memento objects
    State* getState(){return state;}

private:
    State* state;
};

#endif // MEMENTO_H
