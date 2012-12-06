#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(animatedtiles);

    QApplication app(argc, argv);

    MainWindow mainWindow;

    return app.exec();
}
