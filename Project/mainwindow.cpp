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

QString getNameBook(std::string line)
{
    std::string str_result;
    for (int i = 0; line[i] != '|'; ++i) {
        str_result += line[i];
    }
    QString temp = "";
    for (size_t i = 0; i < line.length(); ++i) {
        temp.append(line[i]);
    }
    return temp;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

}

void MainWindow::on_lineEdit_textEdited(const QString &arg1) //toble QString can not be compared with std::string
{
    QKeyEvent *event;
    QString name_book;
    std::string line;
    std::ifstream database ("database.txt");
    if (event->key() == Qt::Key_Enter)
    {
    while (getline(database, line))
    {
        name_book = getNameBook(line);
        if (name_book == arg1) {
            ui->textEdit->setText(name_book);
            break;
        } else {
            //ui->textEdit->setText("name book not found!");
            ui->textEdit->setText("book not found");
        }
    }
    }
}
