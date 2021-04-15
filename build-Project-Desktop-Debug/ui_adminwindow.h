/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adminwindow
{
public:
    QTableWidget *tableWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_add;
    QPushButton *button_change;
    QPushButton *button_delete;
    QPushButton *button_close;

    void setupUi(QWidget *adminwindow)
    {
        if (adminwindow->objectName().isEmpty())
            adminwindow->setObjectName(QString::fromUtf8("adminwindow"));
        adminwindow->resize(447, 237);
        tableWidget = new QTableWidget(adminwindow);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 451, 211));
        widget = new QWidget(adminwindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 210, 451, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        button_add = new QPushButton(widget);
        button_add->setObjectName(QString::fromUtf8("button_add"));

        horizontalLayout->addWidget(button_add);

        button_change = new QPushButton(widget);
        button_change->setObjectName(QString::fromUtf8("button_change"));

        horizontalLayout->addWidget(button_change);

        button_delete = new QPushButton(widget);
        button_delete->setObjectName(QString::fromUtf8("button_delete"));

        horizontalLayout->addWidget(button_delete);

        button_close = new QPushButton(widget);
        button_close->setObjectName(QString::fromUtf8("button_close"));

        horizontalLayout->addWidget(button_close);


        retranslateUi(adminwindow);

        QMetaObject::connectSlotsByName(adminwindow);
    } // setupUi

    void retranslateUi(QWidget *adminwindow)
    {
        adminwindow->setWindowTitle(QApplication::translate("adminwindow", "Form", nullptr));
        button_add->setText(QApplication::translate("adminwindow", "add", nullptr));
        button_change->setText(QApplication::translate("adminwindow", "change", nullptr));
        button_delete->setText(QApplication::translate("adminwindow", "delete", nullptr));
        button_close->setText(QApplication::translate("adminwindow", "close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adminwindow: public Ui_adminwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
