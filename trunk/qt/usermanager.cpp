/*
 * =====================================================================================
 *
 *       Filename:  usermanager.cpp
 *
 *    Description:  用户管理
 *
 *        Version:  1.0
 *        Created:  2010年08月02日 21时29分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Huang Jianchao (), hjc0720@sohu.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "usermanager.h"
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QDir>
#include "accountuser.h"

userManagerDlg::userManagerDlg(QWidget* parent)
    :QDialog(parent)
{
    pAddUserBt = new QPushButton(tr("添加用户")); 
    pEditUserBt = new QPushButton(tr("编辑用户")); 
    pDelUserBt = new QPushButton(tr("删除用户")); 

    QVBoxLayout* pLayout = new QVBoxLayout();
    pLayout->addWidget(pAddUserBt);
    pLayout->addWidget(pEditUserBt);
    pLayout->addWidget(pDelUserBt);

    pUserList = new QListWidget();
    pUserList->setSortingEnabled(true);

    QHBoxLayout* pHLayout = new QHBoxLayout();
    pHLayout->addWidget(pUserList,1);
    pHLayout->addLayout(pLayout);

    pLayout = new QVBoxLayout();
    pLayout->addLayout(pHLayout,1);

    pOK = new QPushButton(tr("返回")); 
    pLayout->addWidget(pOK);

    setLayout(pLayout);

    connect(pOK,SIGNAL(clicked()),this,SLOT(OnClose()));
    connect(pAddUserBt,SIGNAL(clicked()),this,SLOT(AddUser()));
    connect(pEditUserBt,SIGNAL(clicked()),this,SLOT(RenameUser()));
    connect(pDelUserBt,SIGNAL(clicked()),this,SLOT(DelUser()));
}

userManagerDlg::~userManagerDlg()
{
}

void userManagerDlg::initial()
{
    QFile userFile(m_homePath + "/userName");
    if(userFile.open(QIODevice::ReadOnly))
    {
        QTextStream out(&userFile);
        while(!out.atEnd())
        {
            QString userName = out.readLine();
            pUserList->addItem(userName);
       }
    }
    userFile.close();
}

void userManagerDlg::RenameUser()
{
    QString selString =  pUserList->currentItem()->text();
    bool isOk = false;
    QString newString = QInputDialog::getText(this,tr("rename"),tr("user name"),QLineEdit::Normal,selString,&isOk);
    if(isOk&&(newString != selString))
    {
        QFile file(m_homePath + "/" + selString);
        if(file.rename(m_homePath + "/" + newString))
        {
            pUserList->currentItem()->setText(newString);
        }
    }
}

void userManagerDlg::DelUser()
{
    QString selString =  pUserList->currentItem()->text();
    pUserList->removeItemWidget(pUserList->currentItem());
    QDir path(m_homePath);
    path.remove(selString);
}
void userManagerDlg::AddUser()
{
    bool isOk = false;
    QString newString = QInputDialog::getText(this,tr("rename"),tr("user name"),QLineEdit::Normal,QString(),&isOk);
    if(isOk && !newString.isEmpty())
    {
        pUserList->addItem(newString);
        
        AccountUser newUser(newString);
        newUser.setPath(m_homePath + QString("/") + newString);
        newUser.save();
    }
}

void userManagerDlg::OnClose()
{
    QFile userFile(m_homePath + "/userName");
    if(userFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&userFile);
        int nCount = pUserList->count();
        for(int i = 0; i < nCount;i++)
        {
            QString selString =  pUserList->item(i)->text();
            out << selString <<endl;
        }
 
    }
    userFile.close();
    accept();
}
    
