#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass),fileName("accountRecord")
{
    ui->setupUi(this);
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->action_exit,SIGNAL(triggered()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initial()
{
    ifstream ifile;
    ifile.open(fileName.c_str());
    if(ifile)
    {
        m_bank.load(ifile);
        m_cash.load(ifile);
    }
    ifile.close();
}

void MainWindow::save()
{
    ofstream ofile;
    ofile.open(fileName.c_str());
    if(ofile)
    {
        m_bank.save(ofile);
        m_cash.save(ofile);
    }
}
