#pragma once

/*State-klassen kommer sköta det mesta i vårt spel, allt från input till att 
rita ut på skärmen. Anledningen till detta är att State endast har virtual-
funktioner, så att den kan rita ut olika saker i olika states. Vi kanske även
har lite annan input i menyn kontra i spelet, så att State sköter det passar 
ganska bra. Det är här vi kommer ha stateklasser som ärver av får pure virtual  "daddy state"*/
class State
{
public:
    virtual ~State() {}
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};
