#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QMessageBox>
#include <string>
#include <QStandardItemModel>
#include <QtGui>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::fstream order_file("order.txt");

QString nameBookFromOrder()
{
    QString title;
    std::string string_from_file;
    order_file >> string_from_file;
    std::cout << string_from_file;
    for (int i = 0; string_from_file[i] != '|'; ++i) {
        title += string_from_file[i];
    }
    return title;
}

QSqlDatabase db_lib = QSqlDatabase::addDatabase("QSQLITE", "lib_order");

void MainWindow::on_pushButton_clicked()
{
    std::ofstream final_order("final_order.txt");
    int summ_for_score = 0, number_order = 1, account_number = 0;
    QString title, author, price, isbn;
    db_lib.setDatabaseName("/home/peter/Desktop/Course_Project/lib.db");
    db_lib.open();
    QSqlQuery lib(db_lib);
    lib.exec("SELECT title, author, price, isbn FROM books");
    final_order << "Provider: ";
    final_order << "Invoice for payment " << account_number << '\n';
    final_order << "Number" << '\t' << "Products" << '\t' << "Price" << '\n'; //symbyl number of order
    while (lib.next())
    {
        title = lib.value(0).toString();
        author = lib.value(1).toString();
        price = lib.value(2).toString();
        isbn = lib.value(3).toString();
        if (title == nameBookFromOrder())
        {
            final_order << number_order << ' ' << title.toStdString() << ' ' << price.toStdString() << '\n';
            summ_for_score += std::stoi(price.toStdString());
        }
    }
    final_order << "Total: " << summ_for_score << '\n' << "Total vat amount: " << (summ_for_score * 20)/100 + summ_for_score;
    order_file << "order has been paid";
}

QStandardItemModel *model = new QStandardItemModel;
QSqlDatabase db_order = QSqlDatabase::addDatabase("QSQLITE", "order");
void MainWindow::startMainWindow()
{
    QString title_lib, author_lib, price_lib, isbn_lib, title_order, author_order, price_order, isbn_order;
    QStandardItem *item_title, *item_author, *item_price, *item_isbn;
    //Осуществляем запрос
    db_lib.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib.open();
    QSqlQuery lib(db_lib);
    lib.exec("SELECT title, author, price, isbn FROM books");

    /*db_order.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_order.open();
    QSqlQuery order(db_order);
    order.exec("SELECT title, author, price, isbn FROM books"); */

    for (int i_for_tabel = 0; lib.next(); ++i_for_tabel)
    {
        title_lib = lib.value(0).toString(); author_lib = lib.value(1).toString();
        price_lib = lib.value(2).toString(); isbn_lib = lib.value(3).toString();

        //title_order = order.value(0).toString(); author_order = order.value(1).toString();
        //price_order = order.value(2).toString(); isbn_order = order.value(3).toString();
        //if (title_lib == title_order) Сравниваем название книги из библеотеки и из заказа и добавляем в табицу просмотра
        //{
            item_title = new QStandardItem(title_lib); item_author = new QStandardItem(author_lib);
            item_price = new QStandardItem(price_lib); item_isbn = new QStandardItem(isbn_lib);
            model->setItem(i_for_tabel, 0, item_title); model->setItem(i_for_tabel, 1, item_author);
            model->setItem(i_for_tabel, 2, item_price); model->setItem(i_for_tabel, 3, item_isbn);
        //}
    }
    model->setHeaderData(0, Qt::Horizontal, "title book", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "author", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "price", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "number of books", Qt::DisplayRole);
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}
