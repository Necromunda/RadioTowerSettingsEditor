#include "editfilewindow.h"
#include "selectfilewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectFileWindow w;
    w.show();
    return a.exec();
}
