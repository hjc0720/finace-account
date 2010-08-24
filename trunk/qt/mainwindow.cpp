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
#include "addrecorddlg.h"
#include <qmessagebox.h>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QInputDialog>
#include "usermanager.h"

using namespace std;

extern string typeString[PayIncomeTypeCount];

MainWindow::MainWindow(QWidget *parent,QString fileName)
    : QMainWindow(parent), filePath(fileName),tableColumnCount(7)
{
    table = new QTableWidget(this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置table不可修改
    setCentralWidget(table);
    createActions();
    createMenu();
    createContextMenu();

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

    totalPayName = new QLabel(tr("总消费:"),this);
    totalPay     = new QLabel(this);

    statusBar = new QStatusBar(this);

    statusBar->addWidget(totalPay);
    statusBar->addWidget(totalPayName);
    statusBar->addWidget(totalPay);
    setStatusBar(statusBar);

    //recordDlg = new addRecordDlg(this);

    analy = new analysisDlg(this);
    connect(this,SIGNAL(dataRefresh(vector<realRecord>&)),analy,SLOT(refresh(vector<realRecord>&)));
    m_curUser = 0;
}

float MainWindow::getTotalPay()
{
    int nCount = m_vRealRecord.size();
    float sum = 0;
    for(int i = 0; i < nCount; i++)
    {
        record tmpRecord = m_vRealRecord[i].realAccount->getRecordAt(m_vRealRecord[i].recordIndex);
        if(tmpRecord.GetPay() == GetFromWife ||
           tmpRecord.GetPay() ==  GetFromCard ||
           tmpRecord.GetPay() == Salary ||
           tmpRecord.GetPay() == GetCash ||
           tmpRecord.GetPay() == GiveToWife)
            continue;
        sum += tmpRecord.GetPay() / 100.f ;
    }
    return sum;
}

void MainWindow::createActions()
{
    action_save = new QAction(tr("&Save"),this);
    action_save->setShortcut(tr("Ctrl+S"));
    connect(action_save,SIGNAL(triggered()),this,SLOT(save()));

    action_import = new QAction(tr("&Import"),this);
    action_import->setShortcut(tr("Ctrl+I"));
    connect(action_import,SIGNAL(triggered()),this,SLOT(import()));

    action_load = new QAction(tr("&Load"),this);
    action_load->setShortcut(tr("Ctrl+L"));
    connect(action_load,SIGNAL(triggered()),this,SLOT(load()));

    action_exit = new QAction(tr("&Quit"),this);
    action_exit->setShortcut(tr("Ctrl+Q"));
    connect(action_exit,SIGNAL(triggered()),this,SLOT(close()));


    action_analys = new QAction(tr("&Analysis"),this);
    action_analys->setShortcut(tr("Ctrl+A"));
    connect(action_analys,SIGNAL(triggered()),this,SLOT(showAnalys()));

    action_addRecord = new QAction(tr("&Add Record"),this);
    action_addRecord->setShortcut(tr("Ctrl++"));
    connect(action_addRecord,SIGNAL(triggered()),this,SLOT(addRecord()));

    action_modifyRecord = new QAction(tr("&M修改记录"),this);
    action_modifyRecord ->setShortcut(tr("Ctrl+M"));
    connect(action_modifyRecord ,SIGNAL(triggered()),this,SLOT(modifyRecord()));

    action_delRecord = new QAction(tr("&D删除记录"),this);
    action_delRecord->setShortcut(tr("Del"));
    connect(action_delRecord ,SIGNAL(triggered()),this,SLOT(delRecord()));

    action_user_manager = new QAction(tr("用户管理"),this);
    connect(action_user_manager,SIGNAL(triggered()),this,SLOT(userManage()));

    action_changeUser = new QAction(tr("change user"),this);
    connect(action_changeUser,SIGNAL(triggered()),this,SLOT(changeUser()));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(action_save);
    fileMenu->addAction(action_load);
    fileMenu->addAction(action_exit);
    fileMenu->addAction(action_analys);
    fileMenu->addAction(action_import);

    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(action_addRecord);
    editMenu->addAction(action_modifyRecord);
    editMenu->addAction(action_delRecord);
    editMenu->addAction(action_user_manager);
    editMenu->addAction(action_changeUser);
}

void MainWindow::createContextMenu()
{
    table->addAction(action_modifyRecord);
    table->addAction(action_addRecord);
    table->addAction(action_delRecord);
    //table->addAction(pasteAction);
    table->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::showAnalys()
{
    analy->show();
    emit dataRefresh(m_vRealRecord);
}

void MainWindow::changeUser()
{
    QStringList userList;
    for(size_t i = 0; i < m_arUser.size(); ++i)
    {
        userList<<m_arUser[i].getUserName();
    } 
    bool isOk = false;
    QString returnString = QInputDialog::getItem(this,tr("change user"),tr("user Name"),userList,m_curUser,false,&isOk);
    if(isOk)
    {
        m_curUser = max(0,userList.indexOf(returnString));
        m_arUser[m_curUser].load();
        dateChange();
    }
}

void MainWindow::userManage()
{
    save();
    userManagerDlg dlg;
    dlg.m_homePath = filePath;
    dlg.initial();
    dlg.exec();
    load();
}

void MainWindow::delRecord()
{
    int row = table->currentRow();
    if(row < 0)
        return;
    realRecord selRecord = m_vRealRecord[row];

    selRecord.realAccount->delRecord(selRecord.recordIndex);
    dateChange();
}
void MainWindow::modifyRecord()
{
    int row = table->currentRow();
    if(row < 0)
        return;
    realRecord selRecord = m_vRealRecord[row];

    record select = selRecord.realAccount->getRecordAt(selRecord.recordIndex);

    addRecordDlg* recordDlg = new addRecordDlg(this);
    AccountUser& nowUser = m_arUser[m_curUser];
    int nAccount = 0;
    for(int i = 0; i < nowUser.getAccountCount(); i++)
    {
        account& nowAccount = nowUser.getAccount(i);
        recordDlg->addAccountName(QString::fromStdString(nowAccount.getName()));
        if(selRecord.realAccount->getName() == nowAccount.getName())
            nAccount = i;

    }
    recordDlg->updateDlg(nAccount,select.GetDate(),select.GetIncome() - select.GetPay(),select.GetType(),select.GetRemark());

    if(recordDlg->exec() == QDialog::Accepted)
    {
        selRecord.realAccount->delRecord(selRecord.recordIndex);
        record newRecord;
        unsigned long date;
        unsigned long pay,income;
        unsigned char type;
        string remark;
        date = recordDlg->getSetDate();
        pay = recordDlg->getPay();
        income = recordDlg->getIncome();
        type = recordDlg->getType();
        remark = recordDlg->getRemark();
        newRecord.initial(date,pay,type,income,remark);
        account& selectAccount = m_arUser[m_curUser].getAccount(recordDlg->getAccount());
        selectAccount.addRecord(newRecord);
        dateChange();
    }
    delete recordDlg;
}

void MainWindow::addRecord()
{
    //recordDlg->show();
    addRecordDlg* recordDlg = new addRecordDlg(this);
    AccountUser& nowUser = m_arUser[m_curUser];
    for(int i = 0; i < nowUser.getAccountCount(); i++)
    {
        account& nowAccount = nowUser.getAccount(i);
        recordDlg->addAccountName(QString::fromStdString(nowAccount.getName()));
    }

    if(recordDlg->exec() == QDialog::Accepted)
    {
        record newRecord;
        unsigned long date;
        unsigned long pay,income;
        unsigned char type;
        string remark;
        date = recordDlg->getSetDate();
        pay = recordDlg->getPay();
        income = recordDlg->getIncome();
        type = recordDlg->getType();
        remark = recordDlg->getRemark();
        newRecord.initial(date,pay,type,income,remark);
        account& selectAccount = m_arUser[m_curUser].getAccount(recordDlg->getAccount());
        selectAccount.addRecord(newRecord);
        dateChange();
    }
    delete recordDlg;
}

MainWindow::~MainWindow()
{
    delete fileMenu;
    delete action_save;
    delete action_load;
    delete action_exit;

    for(size_t i = 0; i < arInfoLabel.size();++i)
    {
        accountInfoLabel* pInfo = arInfoLabel[i];
        SAFEDELETE(pInfo);
    }
}


void MainWindow::initial()
{
    m_arUser.clear();
    QFile userFile(filePath + "/userName");
    if(userFile.open(QIODevice::ReadOnly))
    {
        QTextStream out(&userFile);
        while(!out.atEnd())
        {
            QString userName = out.readLine();
            AccountUser newUser(userName);
            newUser.setPath(filePath + "/" + userName);
            m_arUser.push_back(newUser);
        }
    }
    userFile.close();
    m_arUser[m_curUser].load();
    for(int i = 0; i < m_arUser[m_curUser].getAccountCount(); ++i)
    {
        account& nowAccount = m_arUser[m_curUser].getAccount(i);
        accountInfoLabel* newLabel = new accountInfoLabel;
        newLabel->setNameText(QString::fromStdString(nowAccount.getName()));
        newLabel->setLeftText(QString::number(nowAccount.getTotalLeft()));
        arInfoLabel.push_back(newLabel);
        statusBar->addWidget(newLabel->accountName);
        statusBar->addWidget(newLabel->accountLeft);
    }

    initialTable();
    //bankLeft->setText(QString::number(m_bank.getTotalLeft()));
    //bankName->setText(QString::fromStdString(m_bank.getName()));
    //cashLeft->setText(QString::number(m_cash.getTotalLeft()));
    //cashName->setText(QString::fromStdString(m_cash.getName()));

    totalPay->setText(QString::number(getTotalPay()));
}

void MainWindow::import()
{
    QString filePath = QFileDialog::getOpenFileName(this,tr("导入文件"));
    m_arUser[m_curUser].import(filePath);
    save();
    dateChange();
}
void MainWindow::save()
{
    QFile userFile(filePath + "/userName");
    if(userFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&userFile);
        for(size_t i = 0; i < m_arUser.size();i++)
        {
            out << m_arUser[i].getUserName() <<endl;
        }
    }
    userFile.close();

    m_arUser[m_curUser].save();
 
}


void MainWindow::load()
{
    if(okToContinue())
    {
        initial();
        emit dataRefresh(m_vRealRecord);
    }
}

void MainWindow::dateChange()
{
    table->clear();
    initialTable();
    emit dataRefresh(m_vRealRecord);
    for(size_t i = 0; i < arInfoLabel.size(); ++i)
    {
        accountInfoLabel* nowInfo = arInfoLabel[i];
        statusBar->removeWidget(nowInfo->accountName);
        statusBar->removeWidget(nowInfo->accountLeft);
        SAFEDELETE(nowInfo);
    }
    AccountUser& nowUser = m_arUser[m_curUser];
    int nAccount = nowUser.getAccountCount();
    arInfoLabel.resize(0);
    for(int i = 0; i < nAccount; ++i)
    {
        accountInfoLabel* nowInfo = new accountInfoLabel;

        statusBar->addWidget(nowInfo->accountName);
        statusBar->addWidget(nowInfo->accountLeft);

        nowInfo->setLeftText(QString::number(nowUser.getAccount(i).getTotalLeft()));
        nowInfo->setNameText(QString::fromStdString(nowUser.getAccount(i).getName()));
        arInfoLabel.push_back(nowInfo);
    }
}

void MainWindow::initialTable()
{
    m_vRealRecord.clear();

    table->setColumnCount(tableColumnCount);
    table->setHorizontalHeaderLabels(QStringList()<<tr("date")<<tr("accountName")<<tr("type")<<tr("pay")<<tr("income")<<tr("left")<<tr("other"));
    QDate start,end;
    start = startDate->date();
    end = endDate->date();
    m_nStartDate = getDate(start.year(),start.month(),start.day());
    m_nEndDate = getDate(end.year(),end.month(),end.day());

    //int bankStart,bankEnd,cashStart,cashEnd;

//    m_bank.getStartEnd(m_nStartDate,m_nEndDate,bankStart,bankEnd);
//    m_cash.getStartEnd(m_nStartDate,m_nEndDate,cashStart,cashEnd);
//    int rowCount = bankEnd - bankStart + cashEnd - cashStart + 2;
    m_arUser[m_curUser].fillAllValidateRecord(m_vRealRecord,m_nStartDate,m_nEndDate);
    int rowCount = (int)m_vRealRecord.size();
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
    for(int i = 0; i < rowCount; i++)
    {
        realRecord& nowReal = m_vRealRecord[i];
        const record& nowRecord = nowReal.realAccount->getRecordAt(nowReal.recordIndex);
        setTableRow(*nowReal.realAccount,nowRecord,nowReal.realAccount->getLeftAt(nowReal.recordIndex),i);
    }
}

void MainWindow::setTableRow(account& nowAccount,const record& nowRecord,float left,int row)
{
    table->item(row,0)->setText(QString::fromStdString(dateToString(nowRecord.GetDate())));
    table->item(row,1)->setText(QString::fromStdString(nowAccount.getName()));
    table->item(row,2)->setText(QString::fromStdString(typeString[(int)nowRecord.GetType()]));
    table->item(row,3)->setText(QString::number(nowRecord.GetPay() / 100.f));
    table->item(row,4)->setText(QString::number(nowRecord.GetIncome() / 100.f));
    table->item(row,5)->setText(QString::number(left));
    table->item(row,6)->setText(QString::fromStdString(nowRecord.GetRemark()));
}

bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r = QMessageBox::warning(this,tr("finace_account"),tr("The document is modified.\nDo you want to save your chnages?"),QMessageBox::Yes | QMessageBox::Default,QMessageBox::No,QMessageBox::Cancel | QMessageBox::Escape);
        if(r == QMessageBox::Yes)
        {
            save();
            return true;
        }
        else
            return false;
    }
    return true;
}
