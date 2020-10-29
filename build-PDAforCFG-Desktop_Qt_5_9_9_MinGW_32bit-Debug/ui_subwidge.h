/********************************************************************************
** Form generated from reading UI file 'subwidge.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWIDGE_H
#define UI_SUBWIDGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_subwidge
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *textEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *subwidge)
    {
        if (subwidge->objectName().isEmpty())
            subwidge->setObjectName(QStringLiteral("subwidge"));
        subwidge->resize(662, 465);
        gridLayout_3 = new QGridLayout(subwidge);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(subwidge);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        textEdit = new QTextEdit(subwidge);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 3);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(264, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton = new QPushButton(subwidge);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_3->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(264, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        label_2 = new QLabel(subwidge);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        textBrowser = new QTextBrowser(subwidge);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout_2->addWidget(textBrowser, 1, 0, 1, 3);


        gridLayout_3->addLayout(gridLayout_2, 2, 0, 1, 3);


        retranslateUi(subwidge);

        QMetaObject::connectSlotsByName(subwidge);
    } // setupUi

    void retranslateUi(QWidget *subwidge)
    {
        subwidge->setWindowTitle(QApplication::translate("subwidge", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("subwidge", "\345\255\227\347\254\246\344\270\262\350\276\223\345\205\245\346\241\206", Q_NULLPTR));
        pushButton->setText(QApplication::translate("subwidge", "\345\210\244\346\226\255\344\270\262", Q_NULLPTR));
        label_2->setText(QApplication::translate("subwidge", "\347\273\223\346\236\234\350\276\223\345\207\272\346\241\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class subwidge: public Ui_subwidge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWIDGE_H
