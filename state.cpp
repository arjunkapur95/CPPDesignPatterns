#include "state.h"

State::State(std::list<std::string> planetName1, std::list<double> planetX,std::list<double> planetY,std::list<double> planetXForce,std::list<double> planetYForce,std::list<double> planetXVelocity,std::list<double> planetYVelocity)
    : planetName(planetName1),
      XPos(planetX),
      YPos(planetY),
      XForce(planetXForce),
      YForce(planetYForce),
      XVel(planetXVelocity),
      YVel(planetYVelocity)
{

}

State::~State()
{

}
