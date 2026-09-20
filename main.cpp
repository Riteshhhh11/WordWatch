//"vocabwidget.h" brings in the blueprint
#include "vocabwidget.h"

//<QApplication> brings in the Qt engine
#include <QApplication>

int main(int argc, char *argv[])
{
    //This is the engine, it initializes the Qt framework
    QApplication a(argc, argv);
    //Creates an object names w out of VocabWidget class
    VocabWidget w;
    //Makes the window appear to the screen
    w.show();
    //exec() is the update() of Qt
    return QApplication::exec();
}
