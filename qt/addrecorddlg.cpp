#include "addrecorddlg.h"
#include "ui_addrecorddlg.h"
#include "../record.h"
#include "../basefunction.h"
#include <string>

using namespace std;
extern string typeString[PayIncomeTypeCount];

addRecordDlg::addRecordDlg(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::addRecordDlg)
{
    m_ui->setupUi(this);
    for(int i  = 0; i < PayIncomeTypeCount; i++)
        m_ui->recordType->addItem(QString::fromStdString(typeString[i]));

    m_ui->date->setDate( QDate::currentDate());
}

addRecordDlg::~addRecordDlg()
{
    delete m_ui;
}

void addRecordDlg::updateDlg(int accountIndex,unsigned long date,long sum, unsigned char type,const  string& remark)
{
    QDate nowDate(getYear(date),getMonth(date),getDay(date));
    m_ui->date->setDate(nowDate);
    m_ui->sum->setText(QString::number(sum / 100.f));
    m_ui->recordType->setCurrentIndex(type);
    m_ui->remark->setText(QString::fromStdString(remark));
    m_ui->accountName->setCurrentIndex(accountIndex);
}

void addRecordDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void addRecordDlg::addAccountName(const QString& name)
{
    m_ui->accountName->addItem(name);
}

unsigned long addRecordDlg::getSetDate()
{
    QDate setDate(m_ui->date->date());
    return getDate(setDate.year(),setDate.month(),setDate.day());
}

unsigned long addRecordDlg::getIncome()
{
    QString sumString = m_ui->sum->text();
    float  lSum = sumString.toFloat();
    if(lSum > 0)
        return (unsigned long)(lSum * 100);
    else
        return 0;
}

unsigned long addRecordDlg::getPay()
{
    QString sumString = m_ui->sum->text();
    float lSum = sumString.toFloat();
    if(lSum < 0)
    {
        lSum = -lSum;
        return (unsigned long )(lSum * 100);
    }
    else
        return 0;
}

unsigned char addRecordDlg::getType()
{
    return (unsigned char)m_ui->recordType->currentIndex();
}

string addRecordDlg::getRemark()
{
    QString remark = m_ui->remark->text();
    return remark.toStdString();
}

int addRecordDlg::getAccount()
{
    return m_ui->accountName->currentIndex();
}
