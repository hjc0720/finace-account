/********************************************************************************
** Form generated from reading ui file 'addrecorddlg.ui'
**
** Created: Sun Jul 11 22:43:10 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDRECORDDLG_H
#define UI_ADDRECORDDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_addRecordDlg
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *accountName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *recordType;
    QGridLayout *gridLayout;
    QDateEdit *date;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *sum;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *remark;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *addRecordDlg)
    {
        if (addRecordDlg->objectName().isEmpty())
            addRecordDlg->setObjectName(QString::fromUtf8("addRecordDlg"));
        addRecordDlg->resize(391, 156);
        gridLayout_2 = new QGridLayout(addRecordDlg);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(addRecordDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        accountName = new QComboBox(addRecordDlg);
        accountName->setObjectName(QString::fromUtf8("accountName"));

        horizontalLayout->addWidget(accountName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(addRecordDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        recordType = new QComboBox(addRecordDlg);
        recordType->setObjectName(QString::fromUtf8("recordType"));

        horizontalLayout_2->addWidget(recordType);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        date = new QDateEdit(addRecordDlg);
        date->setObjectName(QString::fromUtf8("date"));

        gridLayout->addWidget(date, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(addRecordDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        sum = new QLineEdit(addRecordDlg);
        sum->setObjectName(QString::fromUtf8("sum"));

        horizontalLayout_3->addWidget(sum);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(addRecordDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        remark = new QLineEdit(addRecordDlg);
        remark->setObjectName(QString::fromUtf8("remark"));

        horizontalLayout_4->addWidget(remark);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(addRecordDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 2, 0, 1, 2);

#ifndef QT_NO_SHORTCUT
        label_4->setBuddy(accountName);
        label_3->setBuddy(recordType);
        label_2->setBuddy(sum);
        label->setBuddy(remark);
#endif // QT_NO_SHORTCUT

        retranslateUi(addRecordDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), addRecordDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), addRecordDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(addRecordDlg);
    } // setupUi

    void retranslateUi(QDialog *addRecordDlg)
    {
        addRecordDlg->setWindowTitle(QApplication::translate("addRecordDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("addRecordDlg", "\345\270\220\346\210\267\345\220\215(&A)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("addRecordDlg", "\350\256\260\345\275\225\347\261\273\345\236\213(&T)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("addRecordDlg", "\351\207\221\351\242\235(&S)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sum->setToolTip(QApplication::translate("addRecordDlg", "\346\255\243\346\225\260\344\270\272\346\224\266\345\205\245\357\274\214\350\264\237\346\225\260\344\270\272\346\224\257\345\207\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("addRecordDlg", "\345\244\207\346\263\250(&R)", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(addRecordDlg);
    } // retranslateUi

};

namespace Ui {
    class addRecordDlg: public Ui_addRecordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRECORDDLG_H
