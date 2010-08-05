#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <QDir>
#include <QTextStream>
#include "createaccountdlg.h"
#include "accountuser.h"

bool CreateNewUser(const QString& path)
{
    CreateAccountDlg dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        const QString& newUserName = dlg.getNewUserName();
        QFile file(path + QString("/userName"));
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            out << newUserName <<endl;
        }
        file.close();
        const QString& AccountName = dlg.getNewAccountName();
        int initSum;
        dlg.getAccountInitSum(initSum);
        AccountUser newUser(newUserName);
        newUser.setPath(path + QString("/") + newUserName);
        newUser.addAccount(AccountName,initSum);
        newUser.save();
        //AccountUser;
    }
    else
        return false;
    return true;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));

    QDir homeDir(QDir::home());
    if(!homeDir.cd(".finace-account"))
    {
        homeDir.mkdir(".finace-account");
        if(!CreateNewUser(homeDir.path()))
            return 0;
   }
   else if(!homeDir.exists("userName"))
   {
       if(!CreateNewUser(homeDir.path()))
           return 0;
   }
    MainWindow w(NULL,homeDir.path());
    w.m_homePath = homeDir.absolutePath();
    w.initial();
    w.show();
    return a.exec();
}
