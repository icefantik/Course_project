#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include "mainwindow.h"
#include "adminwindow.h"
#include "orderwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    int close_window = 0;
    QString cashiers_replace;
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    orderwindow *orderWindow;
    adminwindow *adminWindow;
    MainWindow *mainWindow;
};

#endif // LOGINWINDOW_H
