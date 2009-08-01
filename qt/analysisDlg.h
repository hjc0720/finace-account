/*
 * =====================================================================================
 *
 *       Filename:  analysisDlg.h
 *
 *    Description:  对收支进行分类分析
 *
 *        Version:  1.0
 *        Created:  2009年07月28日 10时43分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Huang Jianchao (), hjc0720@sohu.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef ANALYSIS_DLG_HJC_20090728
#define ANALYSIS_DLG_HJC_20090728


#include	<QtGui/QDialog>
class QTableWidget;

class analysisDlg : public QDialog { 
    Q_OBJECT
    Q_DISABLE_COPY(analysisDlg)
public:
    explicit analysisDlg(QWidget *parent = 0);
    virtual ~analysisDlg();
private:
    QTableWidget* pResult;
    QPushButton* pOk;
};
#endif
