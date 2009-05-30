#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <string>
#include "../account.h"
using namespace std;

class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createMenu();
    void initial();

 private slots:
    void save();
    void addRecord();

private:
    QTableWidget* table;
    QAction* action_save;
    QAction* action_addRecord;
    QAction* action_exit;
    QMenu* fileMenu;
    QMenu* editMenu;
    account m_bank;
    account m_cash;
    const string fileName;
};

#endif // MAINWINDOW_H
