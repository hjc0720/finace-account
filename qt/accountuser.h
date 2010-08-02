/*
 * =====================================================================================
 *
 *       Filename:  accountuser.h
 *
 *    Description:  user info. include account
 *
 *        Version:  1.0
 *        Created:  07/11/2010 04:06:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Huang Jianchao (), hjc0720@sohu.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ACCOUNTUSER_H
#define ACCOUNTUSER_H

#include <vector>
#include <QString>
#include <vector>
#include "../account.h"


class account;
class QString;

class AccountUser
{
public:
    AccountUser(const QString& name);
    void setPath(const QString& path) {m_path = path;};
    void save()const;
    void load();
    bool import(const QString& path);
    void addAccount(const QString& accountName,long initial);
    int getAccountCount()const {return (int)m_accountArray.size();}
    account& getAccount(int nIndex){return m_accountArray[nIndex];}
    const QString& getUserName()const{return m_name;}
    void fillAllValidateRecord(std::vector<realRecord>& arRealRecord,unsigned long nStart,unsigned long nEnd);
protected:
    std::vector<account> m_accountArray;
//    account m_bank;
//    account m_cash;
    QString m_name;
    QString m_path;
};

#endif // ACCOUNTUSER_H
