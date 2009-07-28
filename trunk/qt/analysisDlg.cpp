
#include	<QTableWidget>

#include	<QPushButton>
#include	"analysisDlg.h"

analysisDlg::analysisDlg(QWidget* parent /* = 0 */ )
    : QDialog(parent)
{
    /*  */
    pResult = new QTableWidget(this);
    pResult->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置table不可修改
    pOk = new QPushButton(this);

}

//analysisDlg::~analysisDlg()
//{
//
//}
//

