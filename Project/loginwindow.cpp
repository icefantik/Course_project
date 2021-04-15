#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"
#include <fstream>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    orderWindow = new orderwindow;
    mainWindow = new MainWindow;
    adminWindow = new adminwindow;
    cashiers_replace = "";
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QSqlDatabase db_cashiers = QSqlDatabase::addDatabase("QSQLITE", "worker"); //function addDatabase is static

void LoginWindow::on_pushButton_clicked()
{
    QMessageBox errEntryBox;
    QString Login = ui->login_edit->text();
    QString Password = ui->password_edit->text();
    //here be connect on database
    db_cashiers.setDatabaseName("/home/peter/Desktop/Project/worker.db");
    db_cashiers.open();
    QSqlQuery db_cas(db_cashiers);
    db_cas.exec("SELECT id, login, password, surname, post FROM workers");
    QString id_cashiers, login_cashiers, password_cashiers, surname_cashiers, post_workers;
    while (db_cas.next())
    {
        id_cashiers = db_cas.value(0).toString();
        login_cashiers = db_cas.value(1).toString();
        password_cashiers = db_cas.value(2).toString();
        surname_cashiers = db_cas.value(3).toString();
        post_workers = db_cas.value(4).toString();
        if (Login == login_cashiers && Password == password_cashiers && post_workers.toStdString() == "Кассир") {
            cashiers_replace = surname_cashiers;
            this->close();
            close_window = 1;
            std::fstream order_file("order.txt");
            if (order_file.is_open()) {
                orderWindow->show();
            } else {
                mainWindow->show();
            }
            break;
        }
        else if (Login == login_cashiers && Password == password_cashiers && post_workers.toStdString() == "Админ")
        {
            this->close();
            adminWindow->show();
            close_window = 1;
            break;
        }
    }
    if (close_window == 0)
    {
        QMessageBox errEntryBox;
        errEntryBox.setWindowTitle("Error");
        errEntryBox.setText("You have an incorrect username or password");
        errEntryBox.exec();
    }
}
