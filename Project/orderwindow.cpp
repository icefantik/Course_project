//#include "mainwindow.h"
#include "orderwindow.h"
#include "ui_orderwindow.h"

#include <QStandardItemModel>
#include <QMessageBox>
#include <fstream>
#include <QTime>
#include <QDate>

#include <iostream>

orderwindow::orderwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderwindow)
{
    ui->setupUi(this);
}

orderwindow::~orderwindow()
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
QStandardItemModel *model_order_window = new QStandardItemModel;
QSqlDatabase db_lib_order = QSqlDatabase::addDatabase("QSQLITE", "lib_order");

void orderwindow::on_pushButton_clicked()
{
    std::cout << "click" << std::endl;
    std::ofstream order_file("order.txt", std::ios::app);

    //order_file << "order has been paid";

    order_file.close();

    QDate cd = QDate::currentDate();
    QString date_in_file = cd.toString();

    QTime ct = QTime::currentTime();
    QString time_in_file = ct.toString();

    std::fstream final_order("final_order.txt");
    int summ_for_score = 0, account_number = 0, number_order = 0;

    db_lib_order.setDatabaseName("/home/peter/Desktop/Course_Project/lib.db");
    db_lib_order.open();
    QSqlQuery lib_num(db_lib_order);

    final_order << "Provider: " << "\n";
    final_order << "Invoice for payment: " << account_number << '\n';
    final_order << "Number\t\tProducts\tPrice\n\n"; //symbyl number of order
    QModelIndex index;
    for (int i = 0; i < sizeTableView; ++i)
    {
        final_order << number_order << ". ";
        index = model_order_window->index(i, 0); //index title
        final_order << index.data().toString().toStdString() << "..................";
        index = model_order_window->index(i, 2); //index price

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
    this->close();
}
/**
void orderwindow::startMainWindow() // not working
{
    QString title_lib, author_lib, price_lib, count_lib, number_of_remaining;
    QStandardItem *item_title, *item_author, *item_price, *item_count;
    //Осуществляем запрос
    db_lib_order.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib_order.open();
    QSqlQuery lib(db_lib_order); QSqlQuery lib_num(db_lib_order);
    lib.exec("SELECT title, author, price, count FROM books");
    std::string line, num_transl;
    int i_for_tabel;
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
                msgBox.setText("The order was marked as already paid. Please put a new file with the order.");
                msgBox.exec();
                this->close();
            }
            else if (str.indexOf(title_lib) == 0 && (std::stoi(count_lib.toStdString()) - std::stoi(priceString(indexStartCount(line), line))) >= 0)
            {
                item_title = new QStandardItem(title_lib); item_author = new QStandardItem(author_lib);
                item_price = new QStandardItem(price_lib); item_count = new QStandardItem(count_lib);

                model_order_window->setItem(i_for_tabel, 0, item_title); model_order_window->setItem(i_for_tabel, 1, item_author);
                model_order_window->setItem(i_for_tabel, 2, item_price); model_order_window->setItem(i_for_tabel, 3, item_count);

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
    }
    sizeTableView = i_for_tabel;
    model_order_window->setHeaderData(0, Qt::Horizontal, "title book", Qt::DisplayRole);
    model_order_window->setHeaderData(1, Qt::Horizontal, "author", Qt::DisplayRole);
    model_order_window->setHeaderData(2, Qt::Horizontal, "price", Qt::DisplayRole);
    model_order_window->setHeaderData(3, Qt::Horizontal, "count books", Qt::DisplayRole);
    ui->orderTableView->setModel(model_order_window);
    ui->orderTableView->resizeRowsToContents();
    ui->orderTableView->resizeColumnsToContents();
}
*/

void orderwindow::on_pushButton_2_clicked()
{
    QString title_lib, author_lib, price_lib, count_lib, number_of_remaining;
    QStandardItem *item_title, *item_author, *item_price, *item_count;
    //Осуществляем запрос
    db_lib_order.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib_order.open();
    QSqlQuery lib(db_lib_order); QSqlQuery lib_num(db_lib_order);
    lib.exec("SELECT title, author, price, count FROM books");
    std::string line, num_transl;
    int i_for_tabel;
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
                msgBox.setText("The order was marked as already paid. Please put a new file with the order.");
                msgBox.exec();
                this->close();
            }
            else if (str.indexOf(title_lib) == 0 && (std::stoi(count_lib.toStdString()) - std::stoi(priceString(indexStartCount(line), line))) >= 0)
            {
                item_title = new QStandardItem(title_lib); item_author = new QStandardItem(author_lib);
                item_price = new QStandardItem(price_lib); item_count = new QStandardItem(count_lib);

                model_order_window->setItem(i_for_tabel, 0, item_title); model_order_window->setItem(i_for_tabel, 1, item_author);
                model_order_window->setItem(i_for_tabel, 2, item_price); model_order_window->setItem(i_for_tabel, 3, item_count);

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
    }
    sizeTableView = i_for_tabel;
    model_order_window->setHeaderData(0, Qt::Horizontal, "title book", Qt::DisplayRole);
    model_order_window->setHeaderData(1, Qt::Horizontal, "author", Qt::DisplayRole);
    model_order_window->setHeaderData(2, Qt::Horizontal, "price", Qt::DisplayRole);
    model_order_window->setHeaderData(3, Qt::Horizontal, "count books", Qt::DisplayRole);
    ui->orderTableView->setModel(model_order_window);
    ui->orderTableView->resizeRowsToContents();
    ui->orderTableView->resizeColumnsToContents();
}
