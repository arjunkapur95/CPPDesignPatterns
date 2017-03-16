#include "universebody.h"
#include "config.h"
#include <QDebug>
#include <QGradient>
#include "informationvisitor.h"
#include<iostream>
#include <QObject>
#include "ui_dialog.h"
#include "dialog.h"
using namespace Ui;
using namespace std;
UniverseBody::UniverseBody(
        UniverseComponentType type,
        const std::string& name,
        const std::string& parentName)
        : UniverseComponent(type, name, parentName)
        , VisitableComponent(type, name, parentName)
        , m_xForce(0)
        , m_yForce(0)
        , m_xVelocity(0.0)
        , m_yVelocity(0.0)
        , m_xPosition(0.0)
        , m_yPosition(0.0)
        , m_radius(1.0)
        , m_mass(1.0)
        , m_color(Qt::white)
{ }

void UniverseBody::render(QPainter& painter) const
{
    Config* config = Config::getInstance();

    //get scaled position and radius
    double x = m_xPosition / config->getDistanceScale();
    double y = m_yPosition / config->getDistanceScale();
    double radius = m_radius / config->getRadiusScale();

    if(config->getUseLogRadius())
    {
        radius = std::log(m_radius / config->getLogPointRadius());
    }

    if(radius < 1)
    {
        painter.setPen(m_color);
        painter.drawPoint(x, y);
    }
    else
    {

        //no outline
        painter.setPen(Qt::NoPen);

        //gradient brush
        QRadialGradient gradient(x, y, radius);
        gradient.setColorAt(0.25, m_color);
        gradient.setColorAt(1, Qt::transparent);

        painter.setBrush(gradient);

        painter.drawEllipse(QPointF(x, y), radius, radius);
    }
}

void UniverseBody::renderLabel(QPainter& painter) const
{
    Config* config = Config::getInstance();

    //get scaled position
    double x = m_xPosition / config->getDistanceScale();
    double y = m_yPosition / config->getDistanceScale();
    //draw the label
    painter.setPen(m_color);
    painter.drawText(QRectF(x, y, 150.0, 50.0), getName().c_str());

}


void UniverseBody::addAttractionTo(UniverseBody &other) const
{
    if(this == &other)
    {
        return;
    }
    double other_mass = other.getMass();
    double dx = m_xPosition - other.getPositionX();
    double dy = m_yPosition - other.getPositionY();
    double distance_sq = dx*dx + dy*dy;
    if(distance_sq == 0.0)
    {
        return;
    }

    double force = GRAVITATIONAL_CONSTANT * m_mass * other_mass / distance_sq;

    double distance = sqrt(distance_sq);

    //normalise the vector {dx, dy} by dividing it by the distance, to get the direction
    other.addForce(force * (dx / distance), force * (dy / distance));
}

void UniverseBody::addAttractionFrom(const UniverseComponent &component)
{
    component.addAttractionTo(*this);
}

void UniverseBody::resetForces()
{
    m_xForce = 0.0;
    m_yForce = 0.0;
}

void UniverseBody::updatePosition(int timestep)
{
     // calculate acceleration
     double xAccel = m_xForce / m_mass;
     double yAccel = m_yForce / m_mass;

     // remember the old velocity
     double oldXVelocity = m_xVelocity;
     double oldYVelocity = m_yVelocity;

     // calculate the new velocity (integrate acceleration)
     m_xVelocity += xAccel * timestep;
     m_yVelocity += yAccel * timestep;

     // calculate the new position (integrate velocity)
     // slightly improved by using the average velocity during this timestep
     m_xPosition += (m_xVelocity + oldXVelocity)/2 * timestep;
     m_yPosition += (m_yVelocity + oldYVelocity)/2* timestep;

}
void UniverseBody::updatePositionRight()
{

     // calculate the new position (integrate velocity)
     // slightly improved by using the average velocity during this timestep
     m_xPosition = m_xPosition+100000000000;
     m_yPosition =m_yPosition;

}
void UniverseBody::updatePositionLeft()
{

     // calculate the new position (integrate velocity)
     // slightly improved by using the average velocity during this timestep
     m_xPosition = m_xPosition-100000000000;
     m_yPosition =m_yPosition;

}
void UniverseBody::updatePositionUp()
{
    m_xPosition = m_xPosition;
    m_yPosition =m_yPosition-100000000000;
}
void UniverseBody::updatePositionDown()
{
    m_xPosition = m_xPosition;
    m_yPosition =m_yPosition+100000000000;
}
void UniverseBody ::accept(UniverseComponentVisitor *visitor)
{
    visitor->Visit(this);
}
void UniverseBody::Compare(double x, double y,std::string *name,double *xPos,double *yPos,double *xForce,double *yForce,double *xVel,double *yVel,bool *check)
{
    Config* config = Config::getInstance();

  double x1 =abs(m_xPosition/config->getDistanceScale());
  std::string s;
  double y1 =abs(m_yPosition/config->getDistanceScale());
   x=abs(x);
   y=abs(y);

   InformationVisitor * visitor = new InformationVisitor();
   double x2=abs(x1-x);
   double y2=abs(y1-y);

  if(x2<20 && y2<20)
  {
       this->accept(visitor);
      *name=visitor->VisitName(this);
      *xPos=visitor->VisitXpos(this);
      *yPos=visitor->VisitYpos(this);
      *xForce=m_xForce;
      *yForce=m_yForce;
      *xVel=m_xVelocity;
      *yVel=m_yVelocity;
      *check=true;

  }
  else
  {
      //std::cout<<"No"<<std::endl;
  }
}
void UniverseBody::CompareRight(double x, double y,double *x3,double* y3)
{
  Config* config = Config::getInstance();
  double x1 =abs(m_xPosition/config->getDistanceScale());
  std::string s;
  double y1 =abs(m_yPosition/config->getDistanceScale());
  x=abs(x);
  y=abs(y);

  double x2=abs(x1-x);
  double y2=abs(y1-y);

  if(x2<20 && y2<20)
  {
     *x3=x1;
     *y3=y1;
  }
  else
  {
      //std::cout<<"No"<<std::endl;
  }
}
void UniverseBody::CountPlanets(int *planets)
{

        *planets+=1;
}
void UniverseBody::CountSuns(int *suns)
{
    if(this->m_radius>696e6)
    {
     *suns+=1;
    }
}

void UniverseBody::IncreaseRadius(double x, double y)
{
    Config* config = Config::getInstance();

  double x1 =abs(m_xPosition/config->getDistanceScale());
   std::string s;
  double y1 =abs(m_yPosition/config->getDistanceScale());
   x=abs(x);
   y=abs(y);

   InformationVisitor *visitor =new InformationVisitor();

   double x2=abs(x1-x);
   double y2=abs(y1-y);

  if(x2<20 && y2<20)
  {

      this->accept(visitor);
      visitor->Visit(this,m_radius);

  }
  else
  {
      //std::cout<<"No"<<std::endl;
  }
}

void UniverseBody::getAll(std::list<string> *planetName, std::list<double> *XPos, std::list<double> *YPos, std::list<double> *XForce, std::list<double> *YForce, std::list<double> *XVelocity, std::list<double> *YVelocity)
{
    planetName->push_back(this->getName());
    XPos->push_back(m_xPosition);
    YPos->push_back(m_yPosition);
    XForce->push_back(m_xForce);
    YForce->push_back(m_yForce);
    XVelocity->push_back(m_xVelocity);
    YVelocity->push_back(m_yVelocity);
}
void UniverseBody::setAll(std::list<string> *planetName, std::list<double> *xPos, std::list<double> *yPos, std::list<double> *XForce, std::list<double> *YForce, std::list<double> *XVelocity, std::list<double> *YVelocity, int *planetArrayCounter)
{
   auto x=xPos->begin();
           std::advance(x,*planetArrayCounter);
    m_xPosition=(*x);

    auto y=yPos->begin();
    std::advance(y,*planetArrayCounter);
    m_yPosition = (*y);

    auto xForce=XForce->begin();
    std::advance(xForce,*planetArrayCounter);
    m_xForce = (*xForce);

    auto yForce=YForce->begin();
    std::advance(yForce,*planetArrayCounter);
    m_yForce = (*yForce);

    auto xVel=XVelocity->begin();
    std::advance(xVel,*planetArrayCounter);
    m_xVelocity = (*xVel);

    auto yVel=YVelocity->begin();
    std::advance(yVel,*planetArrayCounter);
    m_yVelocity = (*yVel);

    *planetArrayCounter += 1;
}


