#ifndef UNIVERSEBODY_H
#define UNIVERSEBODY_H

#include "universecomponent.h"
#include "visitablecomponent.h"

class UniverseBody : public VisitableComponent
{
public:
    UniverseBody(
            UniverseComponentType type,
            const std::string& name,
            const std::string& parentName = "");

    virtual ~UniverseBody() {}

    /*********************************************
     * Inherited methods from UniverseComponent
     * *******************************************/
    //render the subtree
    virtual void render(QPainter &painter) const;
    virtual void renderLabel(QPainter& painter) const;

    //apply the attraction from this component, to the specified leaf
    virtual void addAttractionTo(UniverseBody& body) const;

    //update attractive forces to all components of this object, from the specified component
    virtual void addAttractionFrom(const UniverseComponent& component);

    //reset the accumulated forces to zero
    virtual void resetForces();

    //update the positions of all components of this object
    virtual void updatePosition(int timestep);
    virtual void updatePositionRight();
    virtual void updatePositionLeft();
    virtual void updatePositionUp();
    virtual void updatePositionDown();

    virtual void accept(UniverseComponentVisitor * visitor);
    virtual void Compare(double x,double y,std::string *name, double *xPos,double *yPos,double *xForce,double *yForce,double *xVel,double *yVel,bool *check);
    virtual void CompareRight(double x,double y,double* x1,double* y1);
    virtual void CountPlanets(int * planets);
    virtual void CountSuns(int*suns);
    virtual void IncreaseRadius(double x, double y);


    virtual void getAll(std::list<std::string> *planetName, std::list<double> *planetX,std::list<double> *planetY,std::list<double> *planetXForce,std::list<double> *planetYForce,std::list<double> *planetXVelocity,std::list<double> *planetYVelocity);
    //virtual void IncreaseVelocity(double x,double y);
    virtual void setAll(std::list<std::string> *planetName, std::list<double> *planetX,std::list<double> *planetY,std::list<double> *planetXForce,std::list<double> *planetYForce,std::list<double> *planetXVelocity,std::list<double> *planetYVelocity,int *planetArrayCounter = 0);
   //virtual void IncreaseVelocity(double x ,double y);

    //convert the initial (relative) position and velocity, to an absolute one
    //by translating the position and velocity with the values provided
    void convertRelativeToAbsolute(double xp, double yp, double xv, double yv) {
        m_xPosition += xp;
        m_yPosition += yp;
        m_xVelocity += xv;
        m_yVelocity += yv;
    }


    /*********************************************
     * Accessor methods
     * *******************************************/
    const QColor& getColor() const { return m_color; }
    double getPositionX() const { return m_xPosition; }
    double getPositionY() const { return m_yPosition; }
    double getMass() const { return m_mass; }

    void addForce(double x, double y) { m_xForce += x; m_yForce += y; }
    void setPosition(const double x, const double y) { m_xPosition = x; m_yPosition = y; }
    void setVelocity(const double x, const double y) { m_xVelocity = x; m_yVelocity = y; }
    void setRadius(const double& radius) { m_radius = radius; }
    void setMass(const double& mass) { m_mass = mass; }
    void setColor(const QColor& color) { m_color = color; }


private:
    double m_xForce;
    double m_yForce;
    double m_xVelocity;
    double m_yVelocity;
    double m_xPosition;
    double m_yPosition;
    double m_radius;
    double m_mass;

    bool toggleInformation = false;
    QColor m_color;
};

#endif // UNIVERSEBODY_H
