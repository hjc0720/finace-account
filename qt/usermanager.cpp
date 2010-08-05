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

    pOK = new QPushButton(tr("确定")); 
    pCancel = new QPushButton(tr("取消a"));

    pHLayout = new QHBoxLayout();
    pHLayout->addWidget(pOK);
    pHLayout->addWidget(pCancel);
    pLayout->addLayout(pHLayout);

    setLayout(pLayout);

    connect(pOK,SIGNAL(clicked()),this,SLOT(accept()));
    connect(pCancel,SIGNAL(clicked()),this,SLOT(reject()));
}


userManagerDlg::~userManagerDlg()
{
}

