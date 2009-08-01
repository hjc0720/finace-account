
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
    pResult = new QTableWidget(PayIncomeTypeCount,2,this);
    pResult->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置table不可修改
    pResult->setFixedHeight(400);
    for(int i = 0; i < PayIncomeTypeCount; i++)
    {
        QTableWidgetItem* pItem = new QTableWidgetItem;
        pItem->setText(QString::fromStdString(typeString[i]));
        pResult->setItem(i,0,pItem);
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


