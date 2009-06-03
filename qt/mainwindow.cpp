#include "mainwindow.h"
#include "../basefunction.h"
#include <iostream>
#include <QAction>
#include <QMenuBar>
#include <QTableWidget>
#include <QDateEdit>
#include <QToolBar>
#include <QLabel>
#include <QString>
#include <string>
#include <QStatusBar>
using namespace std;

extern string typeString[PayIncomeTypeCount];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), fileName("../accountRecord"),tableColumnCount(7)
{
    table = new QTableWidget(this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置table不可修改
    setCentralWidget(table);
    createActions();
    createMenu();

    QDate firstDay = QDate::currentDate();
    endDate = new QDateEdit(firstDay,this);
    firstDay.setDate(firstDay.year(),firstDay.month(),1);
    startDate = new QDateEdit(firstDay,this);

    startDateLabel = new QLabel(tr("开始日期"),this);
    endDateLabel = new QLabel(tr("endDate"),this);
    dateToolBar = new QToolBar(tr("Date"));

    dateToolBar->addWidget(startDateLabel);
    dateToolBar->addWidget(startDate);
    dateToolBar->addWidget(endDateLabel);
    dateToolBar->addWidget(endDate);
    dateToolBar->setAllowedAreas(Qt::TopToolBarArea);
    addToolBar(dateToolBar);

    connect(startDate,SIGNAL(dateChanged(QDate)),this,SLOT(dateChange()));
    connect(endDate,SIGNAL(dateChanged(QDate)),this,SLOT(dateChange()));

    bankName = new QLabel(this);
    cashName = new QLabel(this);
    bankLeft = new QLabel(this);
    cashLeft = new QLabel(this);

    statusBar = new QStatusBar(this);
    statusBar->addWidget(bankName);
    statusBar->addWidget(bankLeft);
    statusBar->addWidget(cashName);
    statusBar->addWidget(cashLeft);
    setStatusBar(statusBar);

}

void MainWindow::createActions()
{
    action_save = new QAction(tr("&Save"),this);
    action_save->setShortcut(tr("Ctrl+S"));
   connect(action_save,SIGNAL(triggered()),this,SLOT(save()));

    action_exit = new QAction(tr("&Quit"),this);
    action_exit->setShortcut(tr("Ctrl+Q"));
    connect(action_exit,SIGNAL(triggered()),this,SLOT(close()));

    action_addRecord = new QAction(tr("&Add Record"),this);
    action_addRecord->setShortcut(tr("Ctrl++"));
    connect(action_addRecord,SIGNAL(triggered()),this,SLOT(addRecord()));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(action_save);
    fileMenu->addAction(action_exit);

    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(action_addRecord);
}

void MainWindow::addRecord()
{
}

MainWindow::~MainWindow()
{
    delete fileMenu;
    delete action_save;
    delete action_exit;
}

void MainWindow::initial()
{
    ifstream ifile;
    ifile.open(fileName.c_str());
    if(ifile)
    {
        m_bank.load(ifile);
        m_cash.load(ifile);
    }
    ifile.close();
    initialTable();
    bankLeft->setText(QString::number(m_bank.getTotalLeft()));
    cashLeft->setText(QString::number(m_cash.getTotalLeft()));
    bankName->setText(QString::fromStdString(m_bank.getName()));
    cashName->setText(QString::fromStdString(m_cash.getName()));
}

void MainWindow::save()
{
    ofstream ofile;
    ofile.open(fileName.c_str());
    if(ofile)
    {
        m_bank.save(ofile);
        m_cash.save(ofile);
    }
    ofile.close();
}

void MainWindow::dateChange()
{
        table->clear();
        initialTable();
}

void MainWindow::initialTable()
{
    table->setColumnCount(tableColumnCount);
    table->setHorizontalHeaderLabels(QStringList()<<tr("date")<<tr("accountName")<<tr("type")<<tr("pay")<<tr("income")<<tr("left")<<tr("other"));
    QDate start,end;
    start = startDate->date();
    end = endDate->date();
    m_nStartDate = getDate(start.year(),start.month(),start.day());
    m_nEndDate = getDate(end.year(),end.month(),end.day());
    int bankStart,bankEnd,cashStart,cashEnd;
    m_bank.getStartEnd(m_nStartDate,m_nEndDate,bankStart,bankEnd);
    m_cash.getStartEnd(m_nStartDate,m_nEndDate,cashStart,cashEnd);
    int rowCount = bankEnd - bankStart + cashEnd - cashStart + 2;
    table->setRowCount(rowCount);
    for(int i = 0; i < rowCount; i++)
    {
         QTableWidgetItem *item = new QTableWidgetItem;
         item->setText(QString::number(i + 1));
         table->setVerticalHeaderItem(i,item);

         for(int j = 0; j < tableColumnCount; j++)
         {
             QTableWidgetItem* pItem = table->item(i,j);
             if(!pItem)
             {
                 pItem = new QTableWidgetItem();
                 table->setItem(i,j,pItem);
             }
         }
     }
    int nowRow = 0;
    while(bankStart <= bankEnd && cashStart <= cashEnd)
    {
        record bankRecord = m_bank.getRecordAt(bankStart);
        record cashRecord = m_cash.getRecordAt(cashStart);
        if(cashRecord < bankRecord)
            setTableRow(m_cash,cashRecord,m_cash.getLeftAt(cashStart++),nowRow++);
        else
            setTableRow(m_bank,bankRecord,m_bank.getLeftAt(bankStart++),nowRow++);
    }
    while(bankStart <= bankEnd)
    {
        record bankRecord = m_bank.getRecordAt(bankStart);
        setTableRow(m_bank,bankRecord,m_bank.getLeftAt(bankStart++),nowRow++);
    }
    while(cashStart <= cashEnd)
    {
        record cashRecord = m_cash.getRecordAt(cashStart);
        setTableRow(m_cash,cashRecord,m_cash.getLeftAt(cashStart++),nowRow++);
    }
}

void MainWindow::setTableRow(account& nowAccount,record& nowRecord,float left,int row)
{
    table->item(row,0)->setText(QString::fromStdString(dateToString(nowRecord.GetDate())));
    table->item(row,1)->setText(QString::fromStdString(nowAccount.getName()));
    table->item(row,2)->setText(QString::fromStdString(typeString[(int)nowRecord.GetType()]));
    table->item(row,3)->setText(QString::number(nowRecord.GetPay() / 100.f));
    table->item(row,4)->setText(QString::number(nowRecord.GetIncome() / 100.f));
    table->item(row,5)->setText(QString::number(left));
    table->item(row,6)->setText(QString::fromStdString(nowRecord.GetRemark()));
}
