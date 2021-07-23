#include <QApplication>
#include "infotainmentsystemWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InfotainmentsystemWindow w;
    w.show();
    return a.exec();
}
