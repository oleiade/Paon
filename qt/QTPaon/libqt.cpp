#include <Qt/qapplication.h>
#include <QEventLoop>

#include "mainwindow.h"
#include "libqt.h"
#include "Paon.hh"

#include <iostream>

void        LibQt::run(int ac, char **av, Paon& game)
{
    QApplication    QApp(ac, av);
    MainWindow      window(game);

    window.show();
    QApp.exec();
}

IGraph*     getInstance()
{
    return (new LibQt);
}
