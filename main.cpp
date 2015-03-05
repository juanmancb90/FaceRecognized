#include <QApplication>
#include "mainwindow.h"
//
int main(int argc, char ** argv)
{
    QApplication app( argc, argv );
    MainWindow win;
    win.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
