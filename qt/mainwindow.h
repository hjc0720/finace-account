#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <string>
#include "../account.h"


using namespace std;

class QTableWidget;
class QDateEdit;
class QLabel;
class addRecordDlg;

typedef struct _realRecord
{
    account* realAccount;
    int recordIndex;
}realRecord;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createMenu();
    void initial();
private:
    void initialTable();
    void setTableRow(account& nowAccount,record& nowRecord,float left,int row);
    void createContextMenu();


 private slots:
    void save();
    void addRecord();
    void dateChange();
    void modifyRecord();

private:
    QLabel* bankName;
    QLabel* cashName;
    QLabel* bankLeft;
    QLabel* cashLeft;
    QStatusBar* statusBar;
    QTableWidget* table;
    QAction* action_save;
    QAction* action_addRecord;
    QAction* action_modifyRecord;
    QAction* action_exit;
    QMenu* fileMenu;
    QMenu* editMenu;
    QToolBar* dateToolBar;
    QLabel* startDateLabel;
    QLabel* endDateLabel;
    QDateEdit* startDate;
    QDateEdit* endDate;
    account m_bank;
    account m_cash;
    unsigned long m_nStartDate;
    unsigned long m_nEndDate;
    const string fileName;
    const int tableColumnCount;
    //addRecordDlg* recordDlg;
    vector<realRecord> m_vRealRecord;
};

#endif // MAINWINDOW_H
