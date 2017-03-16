#include "dialog.h"
#include "ui_dialog.h"
#include "universecomposite.h"
#include "universecomponentfactory.h"
#include "universebody.h"
#include "informationvisitor.h"
#include "universecomponentvisitor.h"
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <iostream>
#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <sstream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_width(800)
    , m_height(800)
    , m_paused(false)
    , m_renderZodiacs(true)
    , m_renderLabels(true)
    , m_timestamp(0)
    , m_config(Config::getInstance())
{
    m_config->read("c:\\Studies\\University of sydney\\2016 SEM\\INFO3220\\config.txt");
    m_universe = m_config->parseUniverseBlocks();
    m_zodiacs = m_config->parseZodiacBlocks();
    m_universe->convertRelativeToAbsolute(0,0,0,0);

    //set backdrop to black
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    //make the window appear
    ui->setupUi(this);
    this->resize(m_width, m_height);



    //create the buttons
    m_buttonPause     = new QPushButton("Pause", this);
    m_buttonZodiacs   = new QPushButton("Zodiacs", this);
    m_buttonLabels    = new QPushButton("Labels", this);
    m_buttonZoom      = new QPushButton("Zoom",this);
    m_buttonZoomOut   = new QPushButton("Zoom Out",this);
    m_buttonTimeStep  =new QPushButton("Timestep Increase",this);
    m_buttonTimeStep1  =new QPushButton("Timestep Decrease",this);
    m_buttonRotateLeft = new QPushButton("Rotate Left",this);
    m_buttonRotateRight = new QPushButton("Rotate Right",this);
    m_buttonViewAll   = new QPushButton("View All",this);
    m_buttonSaveState       = new QPushButton("Save State",this);
    m_buttonRestoreState    = new QPushButton("Restore State",this);


    m_buttonPause->setGeometry(QRect(QPoint(0, 0), QSize(100, 50)));
    m_buttonZodiacs->setGeometry(QRect(QPoint(100, 0), QSize(100, 50)));
    m_buttonLabels->setGeometry(QRect(QPoint(200, 0), QSize(100, 50)));
    connect(m_buttonPause, SIGNAL(released()), this, SLOT(togglePause()));
    connect(m_buttonZodiacs, SIGNAL(released()), this, SLOT(toggleZodiacs()));
    connect(m_buttonLabels, SIGNAL(released()), this, SLOT(toggleLabels()));
    m_buttonZoomOut->setGeometry(QRect(QPoint(300, 0), QSize(100, 50)));
    m_buttonZoom->setGeometry(QRect(QPoint(400, 0), QSize(100, 50)));
    m_buttonTimeStep->setGeometry(QRect(QPoint(500, 0), QSize(100, 50)));
     m_buttonTimeStep1->setGeometry(QRect(QPoint(600, 0), QSize(100, 50)));
    connect(m_buttonZoom, SIGNAL(released()), this, SLOT(toggleZoomIn()));
    connect(m_buttonTimeStep, SIGNAL(released()), this, SLOT(toggleTimeStep()));
    connect(m_buttonTimeStep1, SIGNAL(released()), this, SLOT(toogleTimeStepSlow()));
    connect(m_buttonZoomOut, SIGNAL(released()), this, SLOT(toggleZoomOut()));
    m_buttonViewAll->setGeometry(QRect(QPoint(700, 0), QSize(100, 50)));
    m_buttonRotateLeft->setGeometry(QRect(QPoint(250, 100), QSize(100, 50)));
    m_buttonRotateRight->setGeometry(QRect(QPoint(350, 100), QSize(100, 50)));
    connect(m_buttonViewAll, SIGNAL(released()), this, SLOT(toggleViewAll()));
    connect(m_buttonRotateLeft, SIGNAL(released()), this, SLOT(rotateLeft()));
    connect(m_buttonRotateRight, SIGNAL(released()), this, SLOT(rotateRight()));
    m_buttonSaveState->setGeometry(QRect(QPoint(450, 100), QSize(100, 50)));
    m_buttonRestoreState->setGeometry(QRect(QPoint(550, 100), QSize(100, 50)));
    connect(m_buttonSaveState, SIGNAL(released()), this, SLOT(saveState()));
    connect(m_buttonRestoreState, SIGNAL(released()), this, SLOT(restoreState()));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    pause(false);
}

Dialog::~Dialog()
{
    delete ui;
    delete m_timer;
    delete m_buttonPause;
    delete m_buttonZodiacs;
    delete m_buttonLabels;
    delete m_universe;
    delete m_zodiacs;
    delete m_buttonZoom;
    delete m_buttonZoomOut;
    delete m_buttonTimeStep;
    delete m_buttonTimeStep1;
    delete m_buttonViewAll;
    delete m_buttonRotateRight;
    delete m_buttonRotateLeft;
    delete m_buttonSaveState;
    delete m_buttonRestoreState;

}

void Dialog::toggleZodiacs()
{
    m_renderZodiacs = !m_renderZodiacs;
}

void Dialog::toggleLabels()
{
    m_renderLabels = !m_renderLabels;
}

void Dialog::togglePause()
{
    pause(!m_paused);
}
void Dialog::toggleZoomIn()
{
     m_config->zoomIn();

}
void Dialog::toggleZoomOut()
{

    m_config->zoomOut();
}
void Dialog::toggleTimeStep()
{
    m_config->changeTimestepZoom();
}
void Dialog::toogleTimeStepSlow()
{
    m_config->changeTimestepZoomOut();
}

void Dialog::toggleViewAll()
{
    viewAll=!viewAll;
    if(viewAll)
    {
        m_config->ViewAll();
    }
    else
    {
        m_config->Reset();
    }

}
void Dialog::rotateLeft()
{
    rotate=rotate-5;

}
void Dialog::rotateRight()
{
    rotate=rotate+5;

}
 void Dialog::wheelEvent(QWheelEvent *wheel_event)
{
    if(wheel_event->delta()>0)
    {
        m_config->zoomIn();
    }
    else
    {
        m_config->zoomOut();
    }
}
 void Dialog::mouseMoveEvent(QMouseEvent *)
 {

 }
 void Dialog::saveState()
 {
     std::cout<<"happ"<<std::endl;
     //std::vector<std::string> planetName;
     std::list<std::string>planetName;
     //std::map<std::string>planetName;
     //std::array<std::string>planetName;
     std::list<double> Xpos;
     std::list<double> Ypos;
     std::list<double> XForce;
     std::list<double> YForce;
     std::list<double> XVel;
     std::list<double> YVel;

     m_universe->getAll(&planetName,&Xpos,&Ypos,&XForce,&YForce,&XVel,&YVel);

     originator.setState(new State(planetName,Xpos,Ypos,XForce,YForce,XVel,YVel));
     savedStates.push_back(originator.saveStateToMemento());



     Xpos.clear();
     Ypos.clear();
     XForce.clear();
     YForce.clear();
     XVel.clear();
     YVel.clear();
 }
//restoring states from a momento
 void Dialog::restoreState()
 {
     bool ok = false;
     QInputDialog* inputDialog = new QInputDialog();
     QString Text =  inputDialog->getText(NULL,"State Restoration"," ",
                                          QLineEdit::Normal,0,&ok);

     if((!Text.isEmpty()) && (Text.toInt() != 0) && (Text.toInt() <= savedStates.size()))
      {
         int Counter = 0;
         originator.getStateFromMemento(*savedStates[Text.toInt()-1]);
         std::cout<<"check1"<<std::endl;
         m_universe->setAll(
                     originator.getState()->getPlanetName(),
                     originator.getState()->getPosX(),
                     originator.getState()->getPosY(),
                     originator.getState()->getXForce(),
                     originator.getState()->getYForce(),
                     originator.getState()->getXVel(),
                     originator.getState()->getYVel(),
                     &Counter);
     }
     else
     {

     }


 }

void Dialog::mousePressEvent(QMouseEvent *event) {
    switch (event->button()) {

        // On left click (and hold!):
        // Handles setting up a new random planet and it's velocity
        case Qt::LeftButton: {
            std::string name;
            double xPos;
            double yPos;
            double xForce;
            double yForce;
            double xVel;
            double yVel;


            bool check=false;
            left_click_position = mouse_position;
            //pause(!m_paused);
            int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
             std::string s;

            for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
            {
              m_universe->Compare(left_click_position.x()-(m_width/2),left_click_position.y()-(m_height/2),&(name),&(xPos),&(yPos),&(xForce),&(yForce),&(xVel),&(yVel),&(check));

            }

           if(check)
           {
             QString qstr = QString::fromStdString(name);
             ui->browser->setText(" Name " + qstr);
             xPos=(xPos/m_config->getDistanceScale());
             s=std::to_string(xPos);
             qstr = QString::fromStdString(s);
             ui->browser->append(" Xposition " +qstr);

            yPos=(yPos/m_config->getDistanceScale());
            s=std::to_string(yPos);
            qstr = QString::fromStdString(s);
            ui->browser->append(" Yposition " +qstr);


             int xForce1=xForce;
             s=std::to_string(xForce1);
             qstr = QString::fromStdString(s);
             ui->browser->append(" XForce " +qstr);

            int yForce1 =yForce;
            s=std::to_string(yForce1);
            qstr = QString::fromStdString(s);
            ui->browser->append(" YForce " +qstr);

             int xVel1=xVel;
             s=std::to_string(xVel1);
             qstr = QString::fromStdString(s);
             ui->browser->append(qstr);
              ui->browser->append(" Xvel " +qstr);

             int yVel1=yVel;
             s=std::to_string(yVel1);
             qstr = QString::fromStdString(s);
              ui->browser->append(" Yvel " +qstr);
            }

            break;
        }
        case Qt::RightButton:
        {

            double x=0;
            double y=0;
            right_click_position = mouse_position;
        //pause(!m_paused);
            int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
         std::string s;

        for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
        {
          m_universe->CompareRight(right_click_position.x()-(m_width/2),right_click_position.y()-(m_height/2),&x,&y);

        }

        xwidth=x;
        ywidth=y;

        update();


        break;



        }

        default:
            return;
        break;
    }
}
//using mouse release events to perform actions on universe bodies
void Dialog::mouseReleaseEvent(QMouseEvent *event) {
    switch (event->button())
    {

        case Qt::LeftButton:
        {
                left_click_position = mouse_position;

            int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();

            for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
            {
                 m_universe->IncreaseRadius(left_click_position.x()-(m_width/2),left_click_position.y()-(m_height/2));
            }

            break;
        }
        case Qt::RightButton:
        {

        }


        default:
            return;
    }
}
void Dialog::pause(bool pause)
{
    int planets=0;
    if(pause)
    {
        m_timer->stop();
        m_paused = true;
    }
    else
    {
        m_timer->start(1000 / m_config->getFramesPerSecond());
        m_paused = false;
    }
    m_universe->CountPlanets(&planets);
    std::cout<<planets<<std::endl;
}
//Panning objects to the right
void Dialog::PanRight()
{
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
    {
        m_universe->updatePositionRight();
    }
    update();
}
//Panning objects to the left
void Dialog::PanLeft()
{
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
    {
        m_universe->updatePositionLeft();

    }

    update();
}

//panning objects up
void Dialog::PanUp()
{
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
    {
        m_universe->updatePositionUp();

    }
    update();
}
//panning objects down
void Dialog::PanDown()
{
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize()/2; i += step)
    {
        m_universe->updatePositionDown();

    }
    update();
}
//Executing the various key press event
void Dialog::keyPressEvent(QKeyEvent *event)
{

    switch(event->key()) {
    case Qt::Key_Space:
        pause(!m_paused);
        return;
        break;
    case Qt::Key_A:
        PanLeft();
        break;
    case Qt::Key_D:
        PanRight();
        break;
    case Qt::Key_W:
        PanUp();
        break;
    case Qt::Key_S:
        PanDown();
        break;

    default:
        return;
    }
}

void Dialog::nextFrame()
{

    mouse_position = mapFromGlobal(QCursor::pos());//getting the position from the cursor every second


    //reset the forces stored in every object to 0
    m_universe->resetForces();

    //update the forces acting on every object in the universe,
    //from every object in the universe
    m_universe->addAttractionFrom(*m_universe);

    //update the velocity and position of every object in the universe
    int step = m_config->getPhysicsStepSize() / m_config->getOvercalculatePhysicsAmount();
    for(int i = 0; i < m_config->getPhysicsStepSize(); i += step)
    {
        //update physics
        m_universe->updatePosition(step);
        //some time has passed
        m_timestamp += step;
    }

    //update the window (this will trigger paintEvent)
    update();
}

void Dialog::paintEvent(QPaintEvent *event)
{
    //suppress 'unused variable' warning
    Q_UNUSED(event);

    //redraw the universe
    QPainter painter(this);


    //offset the painter so (0,0) is the center of the window
    painter.translate(m_width/2+xwidth, m_height/2+ywidth);//offset for centering the planets
    painter.rotate(rotate);

    if(m_renderZodiacs)
    {
        for(auto zodiac : *m_zodiacs)
        {
            zodiac.render(painter);
        }
    }

    m_universe->render(painter);

    if(m_renderLabels)
    {
        m_universe->renderLabel(painter);
    }
}
//using an event filter for various mouse press events
bool Dialog::eventFilter(QObject *object, QEvent *event) {
    switch (event->type()) {

        case QEvent::MouseButtonPress: {
            QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
            mousePressEvent(mouse_event);
            return true;
        }

        case QEvent::MouseButtonRelease: {
            QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
            mouseReleaseEvent(mouse_event);
            return true;
        }

        case QEvent::MouseMove: {
            QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
            mouseMoveEvent(mouse_event);
            return true;
        }

        case QEvent::Wheel: {
            QWheelEvent *wheel_event = static_cast<QWheelEvent *>(event);
            wheelEvent(wheel_event);
            //event->accept();
            return true;
        }

        default:
            Q_UNUSED(object);
            return false;
    }
}




