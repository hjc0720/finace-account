#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <QDir>
#include "createaccountdlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));

    QDir homeDir(QDir::home());
    if(!homeDir.cd(".finace-account"))
    {
        homeDir.mkdir(".finace-account");
        CreateAccountDlg dlg;
//        dlg.show();
    }
    else if(!homeDir.exists("account"))
    {

    }
    MainWindow w;
    w.initial();
    w.show();
    return a.exec();
}
