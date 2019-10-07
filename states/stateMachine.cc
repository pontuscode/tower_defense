#include "stateMachine.h"
//Tar in en unique_ptr med ett nytt state samt en bool som anger om man vill ersätta det nuvarande statet (poppa stacken) eller bara lägga ovanpå det nuvarande. 
void stateMachine::addState(stateRef _newState, bool _isReplacing)
{
    this->isAdding = true;
    this->isReplacing = _isReplacing;
    this->newState = std::move(_newState);
}

void stateMachine::removeState()
{
    this->isRemoving = true;
}

void stateMachine::processStateChanges()
{
    if(this->isRemoving && !(this->states.empty()))//Vill man poppa stacken och stacken inte är tom går man in här. 
    {
        this->states.pop();
        this->isRemoving = false;
    } 

    if(this->isAdding) //Går in här om man vill lägga till ett nytt state
    {
        if(!(this->states.empty()))
        {
            if(this->isReplacing) //Vill man ersätta nuvarande state så går man in här och poppar. 
            {
                this->states.pop();
            }
        }
        this->states.push(std::move(this->newState)); //Pushar stacken med nya statet. 
        this->states.top()->init(); //Kör init() för det state som ligger överst på stacken. init() laddar in textures och sådant som behövs i sitt state. 
        this->isAdding = false;
    }
}

stateRef &stateMachine::getActiveState()
{
    return this->states.top();
}
