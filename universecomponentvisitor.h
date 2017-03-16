#ifndef UNIVERSECOMPONENTVISITOR_H
#define UNIVERSECOMPONENTVISITOR_H
//#include "universebody.h"
#include <iostream>
using namespace std;
class UniverseBody;
class VisitableComponent;
class UniverseComponent;

class UniverseComponentVisitor
{
public :
    UniverseComponentVisitor(){}
    virtual ~UniverseComponentVisitor(){}
    virtual void Visit(UniverseBody* body,double radius) = 0;
    virtual std::string VisitName(UniverseBody* body)=0;
    virtual double VisitXpos(UniverseBody* body)=0;
    virtual double VisitYpos(UniverseBody* body)=0;

    virtual void Visit(VisitableComponent* part) = 0;
    virtual void Visit(UniverseComponent* comp) = 0;

};

#endif // UNIVERSECOMPONENTVISITOR_H
