#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <loginwindow.h>

adminwindow::adminwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwindow)
{
    ui->setupUi(this);
}

adminwindow::~adminwindow()
{
    delete ui;
}

void adminwindow::on_button_close_clicked() //function end in login window
{
    this->close();
    LoginWindow login_window;
    login_window.open();
}

QSqlDatabase db_lib_admin = QSqlDatabase::addDatabase("QSQLITE", "admin_lib");

void adminwindow::loadDataFromDatabase()
{
    int i_for_tabel = 0;
    QString title, author, price, isbn;
    QTableWidgetItem *item_title, *item_author, *item_price, *item_isbn;
    //Осуществляем запрос
    db_lib_admin.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib_admin.open();
    QSqlQuery query(db_lib_admin);
    query.exec("SELECT title, author, price, isbn FROM books");
    while (query.next())
    {
        title = query.value(0).toString();
        author = query.value(1).toString();
        price = query.value(2).toString();
        isbn = query.value(3).toString();
        item_title = new QTableWidgetItem(title); item_author = new QTableWidgetItem(author);
        item_price = new QTableWidgetItem(price); item_isbn = new QTableWidgetItem(isbn);
        ui->tableWidget->setItem(i_for_tabel, 0, item_title); ui->tableWidget->setItem(i_for_tabel, 1, item_author);
        ui->tableWidget->setItem(i_for_tabel, 2, item_price); ui->tableWidget->setItem(i_for_tabel, 3, item_isbn);
        ++i_for_tabel;
    }
}

void adminwindow::on_button_add_clicked()
{
    db_lib_admin.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib_admin.open();
    QSqlQuery db_add(db_lib_admin);
    db_add.prepare("INSERT INTO books (title, author, price, count)"
                   "VALUES (:title, :author, :price, :count)");


    /**
    db_add.bindValue(":title");
    db_add.bindValue(":author");
    db_add.bindValue(":price");
    db_add.bindValue(":count");
    */
    db_add.exec();
}
