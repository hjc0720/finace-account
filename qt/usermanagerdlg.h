#ifndef USERMANAGERDLG_H
#define USERMANAGERDLG_H

#include <QtGui/QDialog>

namespace Ui {
    class UserManagerDlg;
}

class UserManagerDlg : public QDialog {
    Q_OBJECT
public:
    UserManagerDlg(QWidget *parent = 0);
    ~UserManagerDlg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::UserManagerDlg *m_ui;
};

#endif // USERMANAGERDLG_H
