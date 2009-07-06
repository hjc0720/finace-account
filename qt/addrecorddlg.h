#ifndef ADDRECORDDLG_H
#define ADDRECORDDLG_H

#include <QtGui/QDialog>
#include <string>
using namespace std;

namespace Ui {
    class addRecordDlg;
}

class addRecordDlg : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(addRecordDlg)
public:
    explicit addRecordDlg(QWidget *parent = 0);
    virtual ~addRecordDlg();
    void addAccountName(const QString& name);
    void updateDlg(int accountIndex,unsigned long date,long sum, unsigned char type, const string& remark);
    unsigned long getSetDate();
    unsigned long getPay();
    unsigned long getIncome();
    unsigned char getType();
    string getRemark();
    int getAccount();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::addRecordDlg *m_ui;
    string m_remark;
};

#endif // ADDRECORDDLG_H
