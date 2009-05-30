#include "mainwindow.h"
#include <iostream>
#include <QAction>
#include <QMenuBar>
#include <QTableWidget>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), fileName("accountRecord")
{
    table = new QTableWidget(20,6,this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setCentralWidget(table);
    createActions();
    createMenu();
}

void MainWindow::createActions()
{
    action_save = new QAction(tr("&Save"),this);
    action_save->setShortcut(tr("Ctrl+S"));
   connect(action_save,SIGNAL(triggered()),this,SLOT(save()));

    action_exit = new QAction(tr("&Quit"),this);
    action_exit->setShortcut(tr("Ctrl+Q"));
    connect(action_exit,SIGNAL(triggered()),this,SLOT(close()));

    action_addRecord = new QAction(tr("&Add Record"),this);
    action_addRecord->setShortcut(tr("Ctrl++"));
    connect(action_addRecord,SIGNAL(triggered()),this,SLOT(addRecord()));
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(action_save);
    fileMenu->addAction(action_exit);

    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(action_addRecord);
}

void MainWindow::addRecord()
{
}

MainWindow::~MainWindow()
{
    delete fileMenu;
    delete action_save;
    delete action_exit;
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
    ofile.close();
}
