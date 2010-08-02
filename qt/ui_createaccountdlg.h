/********************************************************************************
** Form generated from reading ui file 'createaccountdlg.ui'
**
** Created: Fri Jul 16 22:30:21 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CREATEACCOUNTDLG_H
#define UI_CREATEACCOUNTDLG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateAccountDlg
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *UserName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *AccountName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *initSum;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CreateAccountDlg)
    {
        if (CreateAccountDlg->objectName().isEmpty())
            CreateAccountDlg->setObjectName(QString::fromUtf8("CreateAccountDlg"));
        CreateAccountDlg->setEnabled(true);
        CreateAccountDlg->resize(249, 149);
        CreateAccountDlg->setMinimumSize(QSize(0, 0));
        CreateAccountDlg->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        CreateAccountDlg->setSizeGripEnabled(true);
        CreateAccountDlg->setModal(true);
        gridLayout = new QGridLayout(CreateAccountDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(CreateAccountDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        UserName = new QLineEdit(CreateAccountDlg);
        UserName->setObjectName(QString::fromUtf8("UserName"));

        horizontalLayout->addWidget(UserName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(CreateAccountDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        AccountName = new QLineEdit(CreateAccountDlg);
        AccountName->setObjectName(QString::fromUtf8("AccountName"));

        horizontalLayout_2->addWidget(AccountName);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(CreateAccountDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        initSum = new QLineEdit(CreateAccountDlg);
        initSum->setObjectName(QString::fromUtf8("initSum"));

        horizontalLayout_3->addWidget(initSum);


        verticalLayout->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(CreateAccountDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(CreateAccountDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateAccountDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateAccountDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateAccountDlg);
    } // setupUi

    void retranslateUi(QDialog *CreateAccountDlg)
    {
        CreateAccountDlg->setWindowTitle(QApplication::translate("CreateAccountDlg", "\350\257\267\350\276\223\345\205\245\346\226\260\347\232\204\345\270\220\346\210\267\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CreateAccountDlg", "\347\224\250\346\210\267\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CreateAccountDlg", "\345\270\220\346\210\267\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CreateAccountDlg", "\345\270\220\346\210\267\345\210\235\345\247\213\351\207\221\351\242\235", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CreateAccountDlg);
    } // retranslateUi

};

namespace Ui {
    class CreateAccountDlg: public Ui_CreateAccountDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCOUNTDLG_H
