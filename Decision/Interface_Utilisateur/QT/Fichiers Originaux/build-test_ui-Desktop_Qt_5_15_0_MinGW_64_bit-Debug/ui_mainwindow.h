/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMenu;
    QAction *actionExit;
    QWidget *centralwidget;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QGraphicsView *graphicsView;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_6;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuUI;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(494, 220);
        actionMenu = new QAction(MainWindow);
        actionMenu->setObjectName(QString::fromUtf8("actionMenu"));
        actionMenu->setCheckable(false);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 20, 71, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(330, 20, 81, 41));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 130, 95, 26));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(40, 20, 91, 91));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(340, 50, 101, 41));
        label_5->setAutoFillBackground(false);
        label_5->setScaledContents(false);
        label_5->setWordWrap(false);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 60, 101, 41));
        label_4->setAutoFillBackground(false);
        label_4->setScaledContents(false);
        label_4->setWordWrap(false);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 110, 101, 41));
        label_6->setAutoFillBackground(false);
        label_6->setScaledContents(false);
        label_6->setWordWrap(false);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 494, 23));
        menuUI = new QMenu(menubar);
        menuUI->setObjectName(QString::fromUtf8("menuUI"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuUI->menuAction());
        menuUI->addAction(actionMenu);
        menuUI->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionMenu->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Action :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Vitesse : ", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "103 km/h", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Feu rouge", nullptr));
        menuUI->setTitle(QCoreApplication::translate("MainWindow", "Fichier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
