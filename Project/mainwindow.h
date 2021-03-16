#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QKeyEvent>
#include <QTextStream>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
