#ifndef INFORMATIONVISITOR_H
#define INFORMATIONVISITOR_H
#include "universecomponentvisitor.h"
#include<iostream>

using namespace std;

class InformationVisitor : public UniverseComponentVisitor
{
public:
    InformationVisitor();

    virtual ~InformationVisitor(){}

     virtual void Visit(UniverseBody* body,double radius);
     virtual void Visit(UniverseBody* body,double xVel,double yVel);
     virtual std::string VisitName(UniverseBody* body);
     virtual double VisitXpos(UniverseBody* body);
     virtual double VisitYpos(UniverseBody* body);
     virtual void Visit(VisitableComponent* part);
     virtual void Visit(UniverseComponent* comp);

protected:
    double m_xForce;
    double m_yForce;


};

#endif // INFORMATIONVISITOR_H
