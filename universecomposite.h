#ifndef UNIVERSECOMPOSITE_H
#define UNIVERSECOMPOSITE_H

#include "universecomponent.h"
#include <string>
#include <vector>


class UniverseComposite : public UniverseComponent {

public:
    UniverseComposite(
            UniverseComponentType type,
            const std::string& name,
            const std::string& parentName = "");
    virtual ~UniverseComposite();

    //build up the composition
    virtual void add(UniverseComponent* component) { m_children.push_back(component); }

    /*********************************************
     * Inherited methods from UniverseComponent
     * *******************************************/
    virtual void render(QPainter& painter) const;
    virtual void renderLabel(QPainter& painter) const;
    virtual void addAttractionTo(UniverseBody& other) const;
    virtual void resetForces();
    virtual void addAttractionFrom(const UniverseComponent& component);
    virtual void updatePosition(int timestep);
    virtual void updatePositionRight();
    virtual void updatePositionLeft();
    virtual void updatePositionUp();
    virtual void updatePositionDown();

    virtual void accept(UniverseComponentVisitor* visitor);
    virtual void Compare(double x,double y,std::string *name, double *xPos,double *yPos,double *xForce,double *yForce,double *xVel,double *yVel,bool * check);
    virtual void CompareRight(double x,double y,double *x1,double *y1);
    virtual void CountPlanets(int *planets);
    virtual void CountSuns(int *suns);
    virtual void IncreaseRadius(double x,double y);

    virtual void getAll(std::list<std::string> *planetName, std::list<double> *planetX,std::list<double> *planetY,std::list<double> *planetXForce,std::list<double> *planetYForce,std::list<double> *planetXVelocity,std::list<double> *planetYVelocity);
    //virtual void IncreaseVelocity(double x,double y);
    virtual void setAll(std::list<std::string> *planetName, std::list<double> *planetX,std::list<double> *planetY,std::list<double> *planetXForce,std::list<double> *planetYForce,std::list<double> *planetXVelocity,std::list<double> *planetYVelocity,int *planetArrayCounter = 0);

    /*********************************************
     * Methods used to enable construction of the universe with relative positions
     * *******************************************/
    void setPosition(double x, double y) { m_xPosition = x; m_yPosition = y; }
    void setVelocity(double x, double y) { m_xVelocity = x; m_yVelocity = y; }

    //propagates the position and velocity of each object down to it's children
    //this should only be called ONCE
    void convertRelativeToAbsolute(double xp, double yp, double xv, double yv);


private:
    std::vector<UniverseComponent*> m_children;

    //used only to enable construction of the universe with relative positions
    double m_xVelocity;
    double m_yVelocity;
    double m_xPosition;
    double m_yPosition;

};

#endif // UNIVERSECOMPOSITE_H
