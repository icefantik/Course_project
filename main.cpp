#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow login_window;
    login_window.open();
    if (login_window.close_window == 1) {
        login_window.close();
    }
    //Connect database with books
    QSqlDatabase db_lib = QSqlDatabase::addDatabase("QSQLITE", "lib");
    db_lib.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib.open();
    QSqlDatabase::removeDatabase("QSQLITE");

    return a.exec();
}
