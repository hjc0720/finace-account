/*
 * =====================================================================================
 *
 *       Filename:  accountuser.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/11/2010 04:07:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Huang Jianchao (), hjc0720@sohu.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "accountuser.h"
#include "../account.h"
#include <fstream>
#include <algorithm>
using namespace std;

AccountUser::AccountUser(const QString& name )
    :m_name(name),m_path("")
{
}

void AccountUser::save()const
{
    if(m_path.count() <= 0)
        return;
    ofstream outFile(m_path.toStdString().c_str()); 
    int nNameLen = m_name.size();
    outFile.write((char*)&nNameLen,sizeof(int));
    outFile.write(m_name.toStdString().c_str(),nNameLen);

    int nAccountCount = m_accountArray.size();
    outFile.write((char*)&nAccountCount,sizeof(int));
    for(int i = 0; i < nAccountCount; i++)
    {
        const account& nowAccount = m_accountArray[i];
        nowAccount.save(outFile);
    }
}

void AccountUser::load()
{
    if(m_path.count() <= 0)
        return;
    ifstream inFile(m_path.toStdString().c_str()); 
    int nNameLen  = 0; 
    inFile.read((char*)&nNameLen,sizeof(int));
    char* name = new char[nNameLen + 1];
    inFile.read(name,nNameLen);
    name[nNameLen] = 0;
    m_name = name;

    int nAccountCount = 0;
    inFile.read((char*)&nAccountCount,sizeof(int));
    m_accountArray.resize(nAccountCount);
    for(int i = 0; i < nAccountCount; i++)
    {
        account& nowAccount = m_accountArray[i];
        nowAccount.load(inFile);
    }
}

void AccountUser::addAccount(const QString& accountName,long initial)
{
    account newAccount(accountName.toStdString(),initial);
    m_accountArray.push_back(newAccount);
}
bool AccountUser::import(const QString& path)
{
    ifstream inFile(path.toStdString().c_str());
    account bankAccount,cashAccount;
    bankAccount.load(inFile);
    cashAccount.load(inFile);
    m_accountArray.push_back(bankAccount);
    m_accountArray.push_back(cashAccount);
    return true;
 }

void AccountUser::fillAllValidateRecord(vector<realRecord>& arRealRecord,unsigned long nStart,unsigned long nEnd)
{
    arRealRecord.resize(0);
    for(size_t i = 0; i < m_accountArray.size();++i)
    {
        account& nowAccount = m_accountArray[i];
        int start,end;
        nowAccount.getStartEnd(nStart,nEnd,start,end);

        realRecord newReal;
        newReal.realAccount = &nowAccount; 
        for(int j = start; j <= end; j++)
        {
            newReal.recordIndex = j;
            arRealRecord.push_back(newReal);
        }
    }
    sort(arRealRecord.begin(),arRealRecord.end());
}
