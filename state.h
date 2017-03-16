#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
#include <list>

class State
{
public:
    virtual ~State();
    State(std::list<std::string> planetName1, std::list<double> planetX,std::list<double> planetY,std::list<double> planetXForce,std::list<double> planetYForce,std::list<double> planetXVelocity,std::list<double> planetYVelocity);
    std::list<std::string>* getPlanetName(){return &planetName;}
    std::list<double>* getPosX(){return &XPos;}
    std::list<double>* getPosY(){return &YPos;}
    std::list<double>* getXForce(){return &XForce;}
    std::list<double>* getYForce(){return &YForce;}
    std::list<double>* getXVel(){return &XVel;}
    std::list<double>* getYVel(){return &YVel;}

private:

    std::list<std::string>planetName;
    std::list<double> XPos,YPos,XForce,YForce,XVel,YVel;
};

#endif // STATE_H
