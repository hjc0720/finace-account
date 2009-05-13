#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <string>
#include "account.h"
using namespace std;
namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initial();

 private slots:
    void save();

private:
    Ui::MainWindowClass *ui;
    account m_bank;
    account m_cash;
    const string fileName;
};

#endif // MAINWINDOW_H
