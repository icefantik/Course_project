#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include <fstream>
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    orderWindow = new orderwindow;
}

MainWindow::~MainWindow()
{
    delete ui;
}

int i_for_tabel = 0, j_for_tabel = 0;
//Таблица вне фунции чтобы хранить две переменные
QStandardItemModel *model = new QStandardItemModel;
//Connect database with books
QSqlDatabase db_lib = QSqlDatabase::addDatabase("QSQLITE", "lib");

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString title, author, price, isbn;
    QStandardItem *item_title, *item_author, *item_price, *item_isbn;
    //Осуществляем запрос
    db_lib.setDatabaseName("/home/peter/Desktop/Project/lib.db");
    db_lib.open();
    QSqlQuery query(db_lib);
    query.exec("SELECT title, author, price, count FROM books");

    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        bool book_not_found = 0;
        while (query.next())
        {
            title = query.value(0).toString();
            author = query.value(1).toString();
            price = query.value(2).toString();
            isbn = query.value(3).toString();
            if (title == ui->lineEdit->text()) {
                item_title = new QStandardItem(title); item_author = new QStandardItem(author);
                item_price = new QStandardItem(price); item_isbn = new QStandardItem(isbn);
                model->setItem(i_for_tabel, 0, item_title); model->setItem(i_for_tabel, 1, item_author);
                model->setItem(i_for_tabel, 2, item_price); model->setItem(i_for_tabel, 3, item_isbn);
                book_not_found = 1;
                ++i_for_tabel;
            }

        }
        if (book_not_found == 0) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Message");
            msgBox.setText("sorry book not found");
            msgBox.exec();
        }
    }
    ui->searchTableView->setModel(model);
    ui->searchTableView->resizeRowsToContents();
    ui->searchTableView->resizeColumnsToContents();
}


void MainWindow::on_EndOrderFormat_clicked()
{
    std::ofstream file("check.txt");
    if (file.is_open())
    {
        LoginWindow lw;
        file << "OOO \"Books shop\"\n";
        QDate cd = QDate::currentDate();
        QString date_in_file = cd.toString();

        QTime ct = QTime::currentTime();
        QString time_in_file = ct.toString();

        file << "Terminal: 00001\n"; //starting write in file
        file << "Cashier: " << lw.cashiers_replace.toStdString() << "              " << date_in_file.toStdString() << " " << time_in_file.toStdString() << "\n";
        QModelIndex index;
        //QStringList list;
        int summ_order = 0, count_product = 0;
        for (int tabel_column = 0; tabel_column < model->rowCount(); ++tabel_column)
        {
            index = model->index(tabel_column, 1);
            file << index.data().toString().toStdString() << "...............";
            index = model->index(tabel_column, 3);
            file << index.data().toString().toStdString();
            summ_order += std::stoi(index.data().toString().toStdString());
            ++count_product;
            file << "\n";
        }
        file << "NDS 10/110";
        file << "Count product in receipt: " << count_product;
        file << "Summ NDS 10/100: " << (summ_order * 20) / 100;
        file.close();
    }
    else
    {
        QMessageBox errEntryBox;
        errEntryBox.setWindowTitle("Error");
        errEntryBox.setText("File not open");
        errEntryBox.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    std::fstream order_file("order.txt");
    if (order_file.is_open()) {
        this->close();
        orderWindow->show();
        //orderwindow orderwin;
        //orderwin.startMainWindow();
    } else {
        QMessageBox errEntryBox;
        errEntryBox.setWindowTitle("Message");
        errEntryBox.setText("You did not put the order file in the folder");
        errEntryBox.exec();
    }
}
