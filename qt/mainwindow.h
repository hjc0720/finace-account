#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <string>
#include "../account.h"
#include "analysisDlg.h"
#include "../account.h"
#include "accountuser.h"
#include <QLabel>
#include "../basefunction.h"


using namespace std;

class QTableWidget;
class QDateEdit;
class addRecordDlg;

class accountInfoLabel
{
public:
    accountInfoLabel(){ accountName = new QLabel; accountLeft = new QLabel;}
    ~accountInfoLabel(){SAFEDELETE(accountName);SAFEDELETE(accountLeft);}
    void setNameText(const QString& text){accountName->setText(text);}
    void setLeftText(const QString& text){accountLeft->setText(text);}

    QLabel* accountName;
    QLabel* accountLeft;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0,QString fileName = QString(tr("../accountRecord")));
    ~MainWindow();
    void createActions();
    void createMenu();
    void initial();
    QString m_homePath;
signals:
    void dataRefresh(vector<realRecord>&);
protected:
    void initialTable();
    void setTableRow(account& nowAccount,const record& nowRecord,float left,int row);
    void createContextMenu();
    float getTotalPay();
    bool okToContinue();


 private slots:
    void save();
    void import(); 
    void load();
    void addRecord();
    void showAnalys();
    void dateChange();
    void modifyRecord();
    void delRecord();
    void userManage();

private:
    vector<accountInfoLabel*> arInfoLabel;
    QLabel* totalPayName;
    QLabel* totalPay;
    QStatusBar* statusBar;
    QTableWidget* table;

    QAction* action_save;
    QAction* action_load;
    QAction* action_newFile;
    QAction* action_addRecord;
    QAction* action_exit;
    QAction* action_import;

    QAction* action_modifyRecord;
    QAction* action_delRecord;
    QAction* action_analys;
    QAction* action_user_manager;
    QAction* action_changeUser;
    QAction* action_AccountManage;

    QMenu* fileMenu;
    QMenu* editMenu;
    QToolBar* dateToolBar;
    QLabel* startDateLabel;
    QLabel* endDateLabel;
    QDateEdit* startDate;
    QDateEdit* endDate;
    QString filePath;
    const int tableColumnCount;
    //addRecordDlg* recordDlg;

    analysisDlg* analy;

private:
    vector<AccountUser> m_arUser;
    int                 m_curUser;
//    account m_bank;
//    account m_cash;
    vector<realRecord> m_vRealRecord;
    unsigned long m_nStartDate;
    unsigned long m_nEndDate;
};

#endif // MAINWINDOW_H
