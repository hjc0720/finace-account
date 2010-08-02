/*
 * =====================================================================================
 *
 *       Filename:  usermanager.h
 *
 *    Description:  用户管理
 *
 *        Version:  1.0
 *        Created:  2010年08月02日 21时29分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Huang Jianchao (), hjc0720@sohu.com
 *        Company:  
 *
 * =====================================================================================
 */


class userManagerDlg : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(addRecordDlg)
public:
    explicit userManagerDlg(QWidget* parent = 0);
    virtual ~userManagerDlg();
}
