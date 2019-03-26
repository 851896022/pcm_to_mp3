/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_dialog
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;

    void setupUi(QDialog *dialog)
    {
        if (dialog->objectName().isEmpty())
            dialog->setObjectName(QStringLiteral("dialog"));
        dialog->resize(814, 30);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dialog->sizePolicy().hasHeightForWidth());
        dialog->setSizePolicy(sizePolicy);
        dialog->setMaximumSize(QSize(100000, 50));
        horizontalLayout = new QHBoxLayout(dialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(dialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(dialog);

        QMetaObject::connectSlotsByName(dialog);
    } // setupUi

    void retranslateUi(QDialog *dialog)
    {
        dialog->setWindowTitle(QApplication::translate("dialog", "\346\240\207\351\242\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialog: public Ui_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
