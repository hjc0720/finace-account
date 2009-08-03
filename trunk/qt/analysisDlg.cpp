
#include	<QTableWidget>

#include	<QGridLayout>
#include	<QPushButton>
#include	"analysisDlg.h"

#include	"../record.h"

extern string typeString[PayIncomeTypeCount];
analysisDlg::analysisDlg(QWidget* parent /* = 0 */ )
    : QDialog(parent)
{
    /*  */
    pResult = new QTableWidget(PayIncomeTypeCount,3,this);
    pResult->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置table不可修改
    pResult->setFixedHeight(400);
    for(int i = 0; i < PayIncomeTypeCount; i++)
    {
        QTableWidgetItem* pItem = new QTableWidgetItem;
        pItem->setText(QString::fromStdString(typeString[i]));
        pResult->setItem(i,0,pItem);

        QTableWidgetItem* pPayItem = new QTableWidgetItem;
        pResult->setItem(i,1,pPayItem);

        QTableWidgetItem* pIncomeItem = new QTableWidgetItem;
        pResult->setItem(i,2,pIncomeItem);
    }

    pOk = new QPushButton("确定",this);
    connect(pOk,SIGNAL(clicked()),this,SLOT(accept()));
    QGridLayout* pMainLayout = new QGridLayout;
    pMainLayout->addWidget(pResult,0,0);
    pMainLayout->addWidget(pOk,1,0,Qt::AlignRight);
    setLayout(pMainLayout);

}

analysisDlg::~analysisDlg()
{

}

void analysisDlg::refresh(vector<realRecord> & vNewReal)
{
    if(!isVisible())
        return;
    float acountPaySum[PayIncomeTypeCount] = {0} ;
    float acountIncomeSum[PayIncomeTypeCount] = {0} ;
    for(int i = 0; i < (int)vNewReal.size(); i++)
    {
        realRecord& nowReal = vNewReal[i];
        account* nowAccount = nowReal.realAccount;
        const record& nowRecord = nowAccount->getRecordAt(nowReal.recordIndex);
        acountPaySum[nowRecord.GetType()] += nowRecord.GetPay() / 100.f;
        acountIncomeSum[nowRecord.GetType()] += nowRecord.GetIncome() / 100.f;
    }
    for(int i = 0; i < PayIncomeTypeCount; i++)
    {
        QTableWidgetItem* pPayItem = pResult->item(i,1);
        pPayItem->setText(QString::number(acountPaySum[i]));

        QTableWidgetItem* pIncomeItem = pResult->item(i,2);
        pIncomeItem->setText(QString::number(acountIncomeSum[i]));
    }
}
