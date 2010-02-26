#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <string>
#include "../account.h"
#include "analysisDlg.h"
#include "../account.h"


using namespace std;

class QTableWidget;
class QDateEdit;
class QLabel;
class addRecordDlg;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createMenu();
    void initial();
signals:
    void dataRefresh(vector<realRecord>&);
private:
    void initialTable();
    void setTableRow(account& nowAccount,record& nowRecord,float left,int row);
    void createContextMenu();
    float getTotalPay();
    bool okToContinue();


 private slots:
    void save();
    void load();
    void addRecord();
    void showAnalys();
    void dateChange();
    void modifyRecord();
    void delRecord();

private:
    QLabel* bankName;
    QLabel* cashName;
    QLabel* bankLeft;
    QLabel* cashLeft;
    QLabel* totalPayName;
    QLabel* totalPay;
    QStatusBar* statusBar;
    QTableWidget* table;

    QAction* action_save;
    QAction* action_load;
    QAction* action_saveAs;
    QAction* action_newFile;
    QAction* action_addRecord;
    QAction* action_exit;

    QAction* action_modifyRecord;
    QAction* action_delRecord;
    QAction* action_analys;

    QMenu* fileMenu;
    QMenu* editMenu;
    QToolBar* dateToolBar;
    QLabel* startDateLabel;
    QLabel* endDateLabel;
    QDateEdit* startDate;
    QDateEdit* endDate;
    string fileName;
    const int tableColumnCount;
    //addRecordDlg* recordDlg;

    analysisDlg* analy;

    QString curFile;
private:
    account m_bank;
    account m_cash;
    vector<realRecord> m_vRealRecord;
    unsigned long m_nStartDate;
    unsigned long m_nEndDate;
};

#endif // MAINWINDOW_H
