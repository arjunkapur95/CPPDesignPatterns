#ifndef VISITABLECOMPONENT_H
#define VISITABLECOMPONENT_H
#include "universecomponent.h"
#include "universecomponentvisitor.h"

class VisitableComponent : public virtual UniverseComponent
{
    public :

    VisitableComponent(UniverseComponentType type,
                       const std::string& name,
                       const std::string& parentName = "")
                       :UniverseComponent(type,name,parentName) { }

    virtual ~VisitableComponent() { }

    //composite operation: render the subtree
    virtual void render(QPainter& painter) const = 0;
    virtual void renderLabel(QPainter& painter) const = 0;

    //composite operation: apply the attraction from this component, to the specified leaf
    virtual void addAttractionTo(UniverseBody& other) const = 0;

    //composite operation: reset the accumulated forces on all sub-components to zero
    virtual void resetForces() = 0;

    //composite operation: update attractive forces to all components of this object, from the specified component
    virtual void addAttractionFrom(const UniverseComponent& component) = 0;

    //composite operation: update the positions of all components of this object
    virtual void updatePosition(int timestep) = 0;
    virtual void updatePositionRight() =0;

    //composite operation: convert relative positions to absolute positions
    //i.e. translate all child objects by the parent's position and velocity
    virtual void convertRelativeToAbsolute(double xp, double yp, double xv, double yv) = 0;


    virtual void accept(UniverseComponentVisitor* visitor) = 0;

};

#endif // VISITABLECOMPONENT_H
