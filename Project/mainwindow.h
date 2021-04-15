#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "orderwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QKeyEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QErrorMessage>
#include <QTime>
#include <QDate>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    orderwindow *orderWindow;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void keyPressEvent(QKeyEvent *event);
    void on_EndOrderFormat_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
