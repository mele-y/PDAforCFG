/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *actionNoepsilon;
    QAction *actionNounit;
    QAction *actionNouse;
    QAction *actiontoG1;
    QAction *actiontoG2;
    QAction *actiontoG3;
    QAction *action_PDA;
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionepsilon;
    QAction *actionunit;
    QAction *actionuse;
    QAction *actionG1;
    QAction *actionG2;
    QAction *actionG3;
    QAction *actionpda;
    QAction *actioninput;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *translateButton;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QPlainTextEdit *GrammerTextEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QTextBrowser *displaytext;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuGNF;
    QMenu *menuSIMPLE;
    QMenu *menu_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 743);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        actionNoepsilon = new QAction(MainWindow);
        actionNoepsilon->setObjectName(QStringLiteral("actionNoepsilon"));
        actionNounit = new QAction(MainWindow);
        actionNounit->setObjectName(QStringLiteral("actionNounit"));
        actionNouse = new QAction(MainWindow);
        actionNouse->setObjectName(QStringLiteral("actionNouse"));
        actiontoG1 = new QAction(MainWindow);
        actiontoG1->setObjectName(QStringLiteral("actiontoG1"));
        actiontoG2 = new QAction(MainWindow);
        actiontoG2->setObjectName(QStringLiteral("actiontoG2"));
        actiontoG3 = new QAction(MainWindow);
        actiontoG3->setObjectName(QStringLiteral("actiontoG3"));
        action_PDA = new QAction(MainWindow);
        action_PDA->setObjectName(QStringLiteral("action_PDA"));
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        actionepsilon = new QAction(MainWindow);
        actionepsilon->setObjectName(QStringLiteral("actionepsilon"));
        actionunit = new QAction(MainWindow);
        actionunit->setObjectName(QStringLiteral("actionunit"));
        actionuse = new QAction(MainWindow);
        actionuse->setObjectName(QStringLiteral("actionuse"));
        actionG1 = new QAction(MainWindow);
        actionG1->setObjectName(QStringLiteral("actionG1"));
        actionG2 = new QAction(MainWindow);
        actionG2->setObjectName(QStringLiteral("actionG2"));
        actionG3 = new QAction(MainWindow);
        actionG3->setObjectName(QStringLiteral("actionG3"));
        actionpda = new QAction(MainWindow);
        actionpda->setObjectName(QStringLiteral("actionpda"));
        actioninput = new QAction(MainWindow);
        actioninput->setObjectName(QStringLiteral("actioninput"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(72, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(71, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        translateButton = new QPushButton(centralwidget);
        translateButton->setObjectName(QStringLiteral("translateButton"));

        gridLayout_3->addWidget(translateButton, 0, 1, 1, 1);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(49, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        horizontalSpacer_6 = new QSpacerItem(49, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        gridLayout_3->addWidget(widget_2, 0, 2, 1, 1);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(widget_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        GrammerTextEdit = new QPlainTextEdit(splitter);
        GrammerTextEdit->setObjectName(QStringLiteral("GrammerTextEdit"));
        GrammerTextEdit->setMinimumSize(QSize(0, 0));
        splitter->addWidget(GrammerTextEdit);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 390, 597));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        displaytext = new QTextBrowser(scrollAreaWidgetContents);
        displaytext->setObjectName(QStringLiteral("displaytext"));
        displaytext->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(displaytext, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget_3, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menuGNF = new QMenu(menu_2);
        menuGNF->setObjectName(QStringLiteral("menuGNF"));
        menuSIMPLE = new QMenu(menu_2);
        menuSIMPLE->setObjectName(QStringLiteral("menuSIMPLE"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionopen);
        menu->addAction(actionsave);
        menu_2->addAction(menuSIMPLE->menuAction());
        menu_2->addAction(menuGNF->menuAction());
        menu_2->addAction(actionpda);
        menuGNF->addAction(actionG1);
        menuGNF->addAction(actionG2);
        menuGNF->addAction(actionG3);
        menuSIMPLE->addAction(actionepsilon);
        menuSIMPLE->addAction(actionunit);
        menuSIMPLE->addAction(actionuse);
        menu_3->addAction(actioninput);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "\345\210\244\346\226\255\344\273\273\346\204\217\344\270\262", Q_NULLPTR));
        actionNoepsilon->setText(QApplication::translate("MainWindow", "\346\266\210\351\231\244epsilon\344\272\247\347\224\237\345\274\217", Q_NULLPTR));
        actionNounit->setText(QApplication::translate("MainWindow", "\346\266\210\351\231\244\345\215\225\344\270\200\344\272\247\347\224\237\345\274\217", Q_NULLPTR));
        actionNouse->setText(QApplication::translate("MainWindow", "\346\266\210\351\231\244\346\227\240\347\224\250\344\272\247\347\224\237\345\274\217", Q_NULLPTR));
        actiontoG1->setText(QApplication::translate("MainWindow", "\350\275\254\346\215\242G1\346\226\207\346\263\225", Q_NULLPTR));
        actiontoG1->setIconText(QApplication::translate("MainWindow", "\350\275\254\346\215\242G1\346\226\207\346\263\225", Q_NULLPTR));
        actiontoG2->setText(QApplication::translate("MainWindow", "\350\275\254\346\215\242G2\346\226\207\346\263\225", Q_NULLPTR));
        actiontoG3->setText(QApplication::translate("MainWindow", "\350\275\254\346\215\242G3\346\226\207\346\263\225", Q_NULLPTR));
        action_PDA->setText(QApplication::translate("MainWindow", "\350\275\254\346\215\242PDA", Q_NULLPTR));
        actionopen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        actionsave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\226\207\344\273\266", Q_NULLPTR));
        actionepsilon->setText(QApplication::translate("MainWindow", "\346\266\210\351\231\244epsilon\344\272\247\347\224\237\345\274\217", Q_NULLPTR));
        actionunit->setText(QApplication::translate("MainWindow", "\346\266\210\351\231\244\345\215\225\344\270\200\344\272\247\347\224\237\345\274\217", Q_NULLPTR));
        actionuse->setText(QApplication::translate("MainWindow", "\346\266\210\351\231\244\346\227\240\347\224\250\344\272\247\347\224\237\345\274\217", Q_NULLPTR));
        actionG1->setText(QApplication::translate("MainWindow", "\350\275\254\346\210\220G1\346\226\207\346\263\225", Q_NULLPTR));
        actionG2->setText(QApplication::translate("MainWindow", "\350\275\254\346\210\220G2\346\226\207\346\263\225", Q_NULLPTR));
        actionG3->setText(QApplication::translate("MainWindow", "\350\275\254\346\210\220G3\346\226\207\346\263\225", Q_NULLPTR));
        actionpda->setText(QApplication::translate("MainWindow", "\350\275\254\346\210\220PDA", Q_NULLPTR));
        actioninput->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\344\273\273\346\204\217\344\270\262", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\346\226\207\346\263\225\350\276\223\345\205\245\346\241\206", Q_NULLPTR));
        translateButton->setText(QApplication::translate("MainWindow", "\346\226\207\346\263\225\350\275\254\346\215\242", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234\345\261\225\347\244\272\346\241\206", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\237\245\347\234\213", Q_NULLPTR));
        menuGNF->setTitle(QApplication::translate("MainWindow", "\350\275\254\346\210\220GNF", Q_NULLPTR));
        menuSIMPLE->setTitle(QApplication::translate("MainWindow", "\345\214\226\347\256\200CFG", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\345\210\244\346\226\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
