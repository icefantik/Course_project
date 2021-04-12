#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QMessageBox>
#include <string>
#include <QStandardItemModel>
#include <QtGui>
#include <QTime>
#include <QDate>

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

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

unsigned int indexStartCount(std::string line)
{
    unsigned int i;
    for (i = line.length()-1; line[i] != '|'; --i)
        ;
    return i;
}

std::string priceString(int start_price_index, std::string line)
{
    std::string result_str;
    for (int i = start_price_index+1; line[i] != '\0'; ++i) {
        result_str += line[i];
    }
    return result_str;
}

int sizeTableView = 0;
const int sizeMassTitles = 1000;
QString *massTitles = new QString[sizeMassTitles];
std::vector <int> massSubOrder, massSubDb;
QStandardItemModel *model = new QStandardItemModel;
QSqlDatabase db_lib = QSqlDatabase::addDatabase("QSQLITE", "lib_order");

void MainWindow::on_pushButton_clicked()
{
    std::ofstream order_file("order.txt", std::ios::app);

    //order_file << "order has been paid";

    order_file.close();

    QDate cd = QDate::currentDate();
    QString date_in_file = cd.toString();

    QTime ct = QTime::currentTime();
    QString time_in_file = ct.toString();

    std::ofstream final_order("final_order.txt");
    int summ_for_score = 0, account_number = 0, number_order = 0;

    db_lib.setDatabaseName("/home/peter/Desktop/Course_Project/lib.db");
    db_lib.open();
    QSqlQuery lib_num(db_lib);

    final_order << "Provider: " << "\n";
    final_order << "Invoice for payment: " << account_number << '\n';
    final_order << "Number\t\tProducts\tPrice\n\n"; //symbyl number of order
    QModelIndex index;
    for (int i = 0; i < sizeTableView; ++i)
    {
        final_order << number_order << ". ";
        index = model->index(i, 0); //index title
        final_order << index.data().toString().toStdString() << "..................";
        index = model->index(i, 2); //index price

        final_order << massSubDb[i] << '*' << index.data().toString().toStdString() << '=' << massSubDb[i] * std::stoi(index.data().toString().toStdString()) << '\n';
        summ_for_score += massSubDb[i] * std::stoi(index.data().toString().toStdString());

        lib_num.prepare("UPDATE books set count = :count WHERE title = :title");
        lib_num.bindValue(":count", massSubDb[i] - massSubOrder[i]);
        lib_num.bindValue(":title", massTitles[i]);
        lib_num.exec();

        ++number_order;
    }
    final_order << "\nTotal: " << summ_for_score << '\n' << "Total vat amount: " << (summ_for_score * 20)/100 + summ_for_score << '\n';
    final_order << date_in_file.toStdString() << ' ' << time_in_file.toStdString() << '\n';
    final_order.close();
}

void MainWindow::startMainWindow()
{
    QString title_lib, author_lib, price_lib, count_lib, number_of_remaining;
    QStandardItem *item_title, *item_author, *item_price, *item_count;
    //Осуществляем запрос
    db_lib.setDatabaseName("/home/peter/Desktop/Course_Project/lib.db");
    db_lib.open();
    QSqlQuery lib(db_lib); QSqlQuery lib_num(db_lib);
    lib.exec("SELECT title, author, price, count FROM books");
    std::string line, num_transl;
    int i_for_tabel, numb;
    for (i_for_tabel = 0; lib.next();)
    {
        title_lib = lib.value(0).toString(); author_lib = lib.value(1).toString();
        price_lib = lib.value(2).toString(); count_lib = lib.value(3).toString();

        std::fstream order_file("order.txt");
        while (getline(order_file, line))
        {
            QString str = QString::fromStdString(line);
            if (line == "order has been paid")
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Message");
                msgBox.setText("The order was marked as already paid");
                msgBox.exec();
                this->close();
            }
            else if (str.indexOf(title_lib) == 0 && (std::stoi(count_lib.toStdString()) - std::stoi(priceString(indexStartCount(line), line))) >= 0)
            {
                item_title = new QStandardItem(title_lib); item_author = new QStandardItem(author_lib);
                item_price = new QStandardItem(price_lib); item_count = new QStandardItem(count_lib);

                numb = std::stoi(count_lib.toStdString()) - std::stoi(priceString(indexStartCount(line), line));

                model->setItem(i_for_tabel, 0, item_title); model->setItem(i_for_tabel, 1, item_author);
                model->setItem(i_for_tabel, 2, item_price); model->setItem(i_for_tabel, 3, item_count);

                massTitles[i_for_tabel] = title_lib;
                massSubDb.push_back(std::stoi(count_lib.toStdString())); //count books form database
                massSubOrder.push_back(std::stoi(priceString(indexStartCount(line), line))); //count books form order

                ++i_for_tabel;
                break;
            }
            else if (std::stoi(count_lib.toStdString()) - std::stoi(priceString(indexStartCount(line), line)) < 0)
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Message");
                msgBox.setText("The number of books in the order is more than in stock: " + title_lib);
                msgBox.exec();
            }
        }
        order_file.close();
        /*if (order_already == 1) {
            break;
        }*/
    }
    sizeTableView = i_for_tabel;
    model->setHeaderData(0, Qt::Horizontal, "title book", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "author", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "price", Qt::DisplayRole);
    model->setHeaderData(3, Qt::Horizontal, "count books", Qt::DisplayRole);
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}
