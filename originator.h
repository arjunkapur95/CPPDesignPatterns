#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include "memento.h"
#include "state.h"

class  Originator {

public:

    void setState(State *state){m_state = state;}

    State* getState(){return m_state;}

    memento* saveStateToMemento(){return (new memento(m_state));}

    void getStateFromMemento(memento Memento){m_state = Memento.getState();}

private:

    State *m_state;
};

#endif // ORIGINATOR_H
