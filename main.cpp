#include "vocabwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VocabWidget w;
    w.show();
    return QApplication::exec();
}
