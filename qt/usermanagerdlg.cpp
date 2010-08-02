#include "usermanagerdlg.h"
#include "ui_usermanagerdlg.h"

UserManagerDlg::UserManagerDlg(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::UserManagerDlg)
{
    m_ui->setupUi(this);
}

UserManagerDlg::~UserManagerDlg()
{
    delete m_ui;
}

void UserManagerDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
