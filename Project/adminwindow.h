#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class adminwindow;
class dialogWindowAdd;
}

class adminwindow : public QWidget
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    void loadDataFromDatabase();
    ~adminwindow();

private slots:
    void on_button_close_clicked();

    void on_button_add_clicked();

private:
    Ui::adminwindow *ui;
};

class dialogWindowAdd : public QDialog
{
    Q_OBJECT
private:
    Ui::dialogWindowAdd *dialogWindowAdmin;
};

#endif // ADMINWINDOW_H
