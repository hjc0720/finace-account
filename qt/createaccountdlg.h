#ifndef CREATEACCOUNTDLG_H
#define CREATEACCOUNTDLG_H

#include <QDialog>
#include <QString>

namespace Ui {
    class CreateAccountDlg;
}

class CreateAccountDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccountDlg(QWidget *parent = 0);
    ~CreateAccountDlg();
    inline QString getNewAccountName()const;

private:
    Ui::CreateAccountDlg *ui;
};

#endif // CREATEACCOUNTDLG_H
