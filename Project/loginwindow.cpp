#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    mainWindow = new MainWindow;
    cashiers_replace = "";
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QSqlDatabase db_cashiers = QSqlDatabase::addDatabase("QSQLITE", "cashiers"); //function addDatabase is static

void LoginWindow::on_pushButton_clicked()
{
    QString Login = ui->login_edit->text();
    QString Password = ui->password_edit->text();
    //here be connect on database
    db_cashiers.setDatabaseName("/home/peter/Desktop/Project/cashiers.db");
    db_cashiers.open();
    QSqlQuery db_cas(db_cashiers);
    db_cas.exec("SELECT id, login, password, surname FROM cashiers");
    QString id_cashiers, login_cashiers, password_cashiers, surname_cashiers;
    while (db_cas.next())
    {
        id_cashiers = db_cas.value(0).toString();
        login_cashiers = db_cas.value(1).toString();
        password_cashiers = db_cas.value(2).toString();
        surname_cashiers = db_cas.value(3).toString();
        if (Login == login_cashiers && Password == password_cashiers) {
            /**QMessageBox msgBox;
            msgBox.setWindowTitle("Message");
            msgBox.setText("You are successfully logged in");
            msgBox.exec();*/
            //LoginWindow lw;
            cashiers_replace = surname_cashiers;

            this->close();
            mainWindow->show();

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
