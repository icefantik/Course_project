#include "mainwindow.h"
#include "ui_mainwindow.h"

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

int i_for_tabel = 0, j_for_tabel = 0;
//Таблица вне фунции чтобы хранить две переменные
QStandardItemModel *model = new QStandardItemModel;
QStandardItem *item_id, *item_name;

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString _id, name, age;

    //Осуществляем запрос
    QSqlQuery query;
    query.exec("SELECT _id, name, age FROM People");

    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        int book_not_found = 0;
        while (query.next())
        {
            _id = query.value(0).toString();
            name = query.value(1).toString();
            age = query.value(2).toString();
            if (name == ui->lineEdit->text()) {
                item_id = new QStandardItem(_id);
                item_name = new QStandardItem(name);
                model->setItem(i_for_tabel, 0, item_id);
                model->setItem(i_for_tabel, 1, item_name);
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
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}
