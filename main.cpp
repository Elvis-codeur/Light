#include <QApplication>
#include <QCoreApplication>
#include <QStringList>
#include "fenprincipale.h"
#include "exportclass.h"
int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    QStringList argument = QCoreApplication::arguments();
    if (argument.size() > 1)
    {
        Fenprincipale fen;
        fen.open_file(argument[1]);
        fen.showMaximized();
        return app.exec();
    }
    else
    {
        Fenprincipale fen;
        fen.showMaximized();
        return app.exec();
    }



}
