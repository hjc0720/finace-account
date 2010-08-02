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

QString CreateAccountDlg::getNewUserName()const
{
    return ui->UserName->text();
}
QString CreateAccountDlg::getNewAccountName()const
{
    return ui->AccountName->text();
}

bool CreateAccountDlg::getAccountInitSum(int& sum)const
{
    const QString& initSum = ui->initSum->text();
    bool isok = false;
    sum = initSum.toInt(&isok);
    return isok;
}

