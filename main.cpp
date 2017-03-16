#include "dialog.h"
#include <QApplication>
#include <iostream>

using namespace std;


bool planetsSize()
{
    int x=0;
    Config* config = Config::getInstance();
    config->read("G:\\Studies\\University of sydney\\2016 SEM\\INFO3220\\config.txt");
    UniverseComponent* m_universe;

    m_universe = config->parseUniverseBlocks();
    m_universe->CountPlanets(&x);

    if(x==37)
    {
        return true;
    }
    else
    {
        return false;
    }

}
bool countSuns()
{
    int x;
    Config* config = Config::getInstance();
    config->read("G:\\Studies\\University of sydney\\2016 SEM\\INFO3220\\config.txt");
    UniverseComponent* m_universe;

    m_universe = config->parseUniverseBlocks();
    m_universe->CountSuns(&x);
    std::cout<<x<<std::endl;
    if(x>1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    std::cout<<"hello"<<std::endl;
    boolean check=false;

   check=planetsSize();

   if(check)
   {
        std::cout<<"success"<<std::endl;
   }
    else
    {
        std::cout<<"failed"<<std::endl;
    }
   check=false;
   check=countSuns();
   if(check)
   {
       std::cout<<"success"<<std::endl;
    }
else
   {
       std::cout<<"Failure"<<std::endl;
   }
    return a.exec();






}
