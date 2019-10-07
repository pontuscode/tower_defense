#pragma once
#include <memory>
#include <stack>
#include "state.h"

/*stateMachine är motorn som ser till att vi kan byta mellan olika States. Detta görs med hjälp av en unique_ptr som pekar på olika States. 
stateMachine i sig är av typen stack, vilket gör att man kan pusha och poppa dess states på stacken. Det är smidigt eftersom man kanske vill stapla states på varann 
utan att nödvändigtvis stänga ner det gamla statet. Pausar man spelet läggs pausState ovanpå gameState på stacken, väljer man New Game i Main Menu poppas det menuState  och ersätts med gameState. */

typedef std::unique_ptr<State> stateRef;

class stateMachine
{
public:
    stateMachine() {}
    ~stateMachine() {}
    
    void addState(stateRef _newState, bool _isReplacing = true);
    void removeState();
    void processStateChanges();

    stateRef &getActiveState(); 

private:
    std::stack<stateRef> states;
    stateRef newState;

    bool isRemoving;
    bool isAdding;
    bool isReplacing;
};
