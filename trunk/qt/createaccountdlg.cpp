#include "createaccountdlg.h"
#include "ui_createaccountdlg.h"

CreateAccountDlg::CreateAccountDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccountDlg)
{
    ui->setupUi(this);
}

CreateAccountDlg::~CreateAccountDlg()
{
    delete ui;
}

inline QString CreateAccountDlg::getNewAccountName()const
{
    return ui->NewAccountName->text();
}
