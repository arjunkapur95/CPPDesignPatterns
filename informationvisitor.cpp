#include "informationvisitor.h"
#include <iostream>
#include "universebody.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "QTextBrowser"

using namespace std;
using namespace Ui;
InformationVisitor::InformationVisitor() :
    m_xForce(0), m_yForce(0)
{}


void InformationVisitor::Visit(VisitableComponent *part)
{
    //std::cout<<part->getName()<<std::endl;
}
void InformationVisitor::Visit(UniverseBody *body,double radius)
{
    body->setRadius(radius=radius*30);
}
void InformationVisitor::Visit(UniverseBody *body, double xVel, double yVel)
{
    body->setVelocity(xVel*2,yVel*2);
}

void InformationVisitor::Visit(UniverseComponent *comp)
{
   //std::cout<<"name"<<std::endl;
}
std::string InformationVisitor::VisitName(UniverseBody *body)
{
    return body->getName();
}
double InformationVisitor::VisitXpos(UniverseBody *body)
{
    return body->getPositionX();
}

double InformationVisitor::VisitYpos(UniverseBody *body)
{
    return body->getPositionY();
}


