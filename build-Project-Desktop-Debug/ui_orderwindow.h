/********************************************************************************
** Form generated from reading UI file 'orderwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERWINDOW_H
#define UI_ORDERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_orderwindow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTableView *orderTableView;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *orderwindow)
    {
        if (orderwindow->objectName().isEmpty())
            orderwindow->setObjectName(QString::fromUtf8("orderwindow"));
        orderwindow->resize(763, 377);
        layoutWidget = new QWidget(orderwindow);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 591, 311));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        orderTableView = new QTableView(layoutWidget);
        orderTableView->setObjectName(QString::fromUtf8("orderTableView"));

        verticalLayout->addWidget(orderTableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(orderwindow);

        QMetaObject::connectSlotsByName(orderwindow);
    } // setupUi

    void retranslateUi(QWidget *orderwindow)
    {
        orderwindow->setWindowTitle(QApplication::translate("orderwindow", "Form", nullptr));
        pushButton->setText(QApplication::translate("orderwindow", "Invoice for payment", nullptr));
        pushButton_2->setText(QApplication::translate("orderwindow", "loadOrder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class orderwindow: public Ui_orderwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERWINDOW_H
