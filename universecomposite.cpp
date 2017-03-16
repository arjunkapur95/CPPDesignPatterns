#include "universecomposite.h"
#include "universebody.h"
#include "universecomponent.h"

UniverseComposite::UniverseComposite(
        UniverseComponentType type,
        const std::string& name,
        const std::string& parentName)
        : UniverseComponent(type, name, parentName)
        , m_xVelocity(0.0)
        , m_yVelocity(0.0)
        , m_xPosition(0.0)
        , m_yPosition(0.0)
{ }

UniverseComposite::~UniverseComposite()
{
    for(UniverseComponent* child : m_children) {
        delete child;
    }
}


//render the subtree
void UniverseComposite::render(QPainter& painter) const
{
    for(UniverseComponent* child : m_children)
    {
        child->render(painter);
    }
}

void UniverseComposite::renderLabel(QPainter& painter) const
{
    for(UniverseComponent* child : m_children)
    {
        child->renderLabel(painter);
    }
}


//apply the attraction from this component, to the specified leaf
void UniverseComposite::addAttractionTo(UniverseBody& other) const
{
    for(UniverseComponent* child : m_children)
    {
        child->addAttractionTo(other);
    }
}

void UniverseComposite::resetForces()
{
    for(UniverseComponent* child : m_children)
    {
        child->resetForces();
    }
}

//update attractive forces to all components of this object, from the specified component
void UniverseComposite::addAttractionFrom(const UniverseComponent& component)
{
    for(UniverseComponent* child : m_children)
    {
        child->addAttractionFrom(component);
    }
}

//update the positions of all components of this object
void UniverseComposite::updatePosition(int timestep)
{
    for(UniverseComponent* child : m_children)
    {
        child->updatePosition(timestep);
    }
}
void UniverseComposite::updatePositionRight()
{

    for(UniverseComponent* child : m_children)
    {
        child->updatePositionRight();
    }
}
void UniverseComposite::accept(UniverseComponentVisitor *visitor)
{
    for(UniverseComponent* child : m_children)
    {
        child->accept(visitor);
        visitor->Visit(child);
    }
}


void UniverseComposite::CountSuns(int *suns)
{
    for(UniverseComponent *child :m_children)
    {
        child->CountSuns(&(*suns));
    }
}

void UniverseComposite::convertRelativeToAbsolute(double xp, double yp, double xv, double yv)
{
    xp += m_xPosition;
    yp += m_yPosition;
    xv += m_xVelocity;
    yv += m_yVelocity;
    for(UniverseComponent* child : m_children)
    {
        child->convertRelativeToAbsolute(xp, yp, xv, yv);
    }
}
void UniverseComposite::Compare(double x, double y,std::string *name,double *xPos,double *yPos,double *xForce,double*yForce,double *xVel,double*yVel,bool *check)
{
    for(UniverseComponent* child : m_children)
    {
        child->Compare(x,y,&(*name),&(*xPos),&(*yPos),&(*xForce),&(*yForce),&(*xVel),&(*yVel),&(*check));

    }
}
void UniverseComposite::CompareRight(double x, double y,double* x3, double* y3)
{
    for(UniverseComponent * child :m_children)
    {
        child->CompareRight(x,y,&(*x3),&(*y3));
    }
}
void UniverseComposite::CountPlanets(int *planets)
{
    for(UniverseComponent * child : m_children)
    {
        child->CountPlanets(&(*planets));
    }
}
void UniverseComposite::updatePositionLeft()
{
    for(UniverseComponent* child : m_children)
    {
        child->updatePositionLeft();
    }
}
void UniverseComposite::updatePositionUp()
{
    for(UniverseComponent* child : m_children)
    {
        child->updatePositionUp();
    }
}
void UniverseComposite::updatePositionDown()
{
    for(UniverseComponent* child : m_children)
    {
        child->updatePositionDown();
    }
}
void UniverseComposite::IncreaseRadius(double x, double y)
{
    for(UniverseComponent* child :m_children)
    {
        child->IncreaseRadius(x,y);
    }
}
void UniverseComposite::getAll(std::list<string> *planetName, std::list<double> *planetX, std::list<double> *planetY, std::list<double> *planetXForce, std::list<double> *planetYForce, std::list<double> *planetXVelocity, std::list<double> *planetYVelocity)
{
    for(UniverseComponent* child :m_children)
    {
        child->getAll(&(*planetName),&(*planetX),&(*planetY),&(*planetXForce),&(*planetYForce),&(*planetXVelocity),&(*planetYVelocity));


    }
}
void UniverseComposite::setAll(std::list<string> *planetName, std::list<double> *planetX, std::list<double> *planetY, std::list<double> *planetXForce, std::list<double> *planetYForce, std::list<double> *planetXVelocity, std::list<double> *planetYVelocity, int *planetArrayCounter)
{
    for(UniverseComponent * child :m_children)
    {
        child->setAll(&(*planetName),&(*planetX),&(*planetY),&(*planetXForce),&(*planetYForce),&(*planetXVelocity),&(*planetYVelocity),&(*planetArrayCounter));
    }
}



