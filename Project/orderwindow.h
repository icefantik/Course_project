#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class orderwindow;
}

class orderwindow : public QWidget
{
    Q_OBJECT

public:
    //void startMainWindow();
    explicit orderwindow(QWidget *parent = nullptr);
    ~orderwindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::orderwindow *ui;
};



#endif // ORDERWINDOW_H
