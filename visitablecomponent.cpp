#include "visitablecomponent.h"

void VisitableComponent::accept(UniverseComponentVisitor *visitor)
{
    visitor->Visit(this);
}
