#ifndef DIALOG_H
#define DIALOG_H

#include "config.h"
#include "universecomponent.h"
#include "zodiac.h"
#include <QDialog>
#include <QTimer>
#include <list>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>
#include "originator.h"
#include <QInputDialog>

#include <QMessageBox>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT




public:
    explicit Dialog(QWidget *parent = 0);
    virtual ~Dialog();
    Ui::Dialog* ui;
    //void mouseMoveEvent(QMouseEvent *ev);
    //void mousePressEvent(QMouseEvent *ev);
    //void leaveEvent(QEvent *);

    //int x,y;
     QPoint mouse_position;
     QPointF left_click_position;
     QPointF right_click_position;

signals:

    //void Mouse_Pressed();
    //void Mouse_Pos();
    //void Mouse_Left();
private slots:
    //prepare the next frame, called by the timer
    void nextFrame();
    //toggle the simultation's pause state
    void togglePause();
    //toggle rendering of Zodiacs
    void toggleZodiacs();
    //toggle rendering of labels
    void toggleLabels();

    void toggleZoomIn();
    void toggleZoomOut();
    void toggleTimeStep();
    void toogleTimeStepSlow();
    void toggleViewAll();
    void rotateLeft();
    void rotateRight();
    void saveState();
    void restoreState();

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    bool eventFilter(QObject *, QEvent *);


private:
    //method called when the window is being redrawn
    void paintEvent(QPaintEvent *event);
    //pause (or unpause) the simulation
    void pause(bool pause);
    void PanRight();
    void PanLeft();
    void PanUp();
    void PanDown();

    //handle key presses
    void keyPressEvent(QKeyEvent *event);

private:

    QTimer* m_timer; //Timer object for triggering updates

    //buttons for UI
    QPushButton* m_buttonPause;
    QPushButton* m_buttonZodiacs;
    QPushButton* m_buttonLabels;
    QPushButton* m_buttonZoom;
    QPushButton* m_buttonZoomOut;
    QPushButton* m_buttonTimeStep;
    QPushButton* m_buttonTimeStep1;
    QPushButton* m_buttonViewAll;
    QPushButton* m_buttonRotateRight;
    QPushButton* m_buttonRotateLeft;
    QPushButton* m_buttonSaveState;
    QPushButton* m_buttonRestoreState;

    int m_width; //width of the window
    int m_height; //height of the window
    double xwidth;
    double ywidth;
    bool m_paused; //is the simulation paused?
    bool m_renderZodiacs; //should Zodiacs be rendered?
    bool m_renderLabels; //should labels be rendered?
    long m_timestamp; //simulation time since simulation start
    UniverseComponent* m_universe; //The universe
    std::list<Zodiac>* m_zodiacs; //Vector of zodiac lines
    Config* m_config; //the singleton config instance
    boolean viewAll=false;
    double rotate=0;
    std::vector<memento*> savedStates; //Caretaker - Keeps track of all the saved state
    Originator originator; //For facilitating the saving and restoring of states

};

#endif // DIALOG_H
