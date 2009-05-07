#include "menu.h"
#include <iostream>
#include "account.h"
#include "record.h"
#include "basefunction.h"
using namespace std;
extern account g_bank;
extern account g_cash;
extern string typeString[PayIncomeTypeCount];
//unsigned long g_dateShow = 0;
	
void mainQuitFun(CMenu** nowMenu)
{
	*nowMenu = (*nowMenu)->getParent();
}

void addRecord(CMenu** nowMenu)
{
	int nAccount = 0;
	do{
		cout<<"1、"<<g_bank.getName()<< endl;
		cout<<"2、"<<g_cash.getName() << endl;
		cout<<"0、返回"<<endl;
		cout<<"请选择帐号：";
		cin >> nAccount;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(nAccount < 0 || nAccount > 2);
	account* selectAccount = NULL;
	switch(nAccount)
	{
		case 1:
			selectAccount = &g_bank;
			break;
		case 2:
			selectAccount = &g_cash;
			break;
		case 0:
			return;
	}
	record newRecord;
	unsigned long date;
	long pay = 0;
	int type;
	long income = 0;
	float sum;
	string remark;
	do{
		string date_string;
		cout << "请输入日期(yyyy-month-day):";
		cin >> date_string;
		date = stringToDate(date_string);
	}while(date == 0);

	do{
		for(int i = 0; i < PayIncomeTypeCount; i++)
			cout<<i + 1 <<"、 "<<typeString[i]<<endl;
		cout <<"请选择支付类型：";
		cin >> type;
		type--;
	}while(type < 0 || type >= PayIncomeTypeCount); 

	do{
		cout << "请输入金额(负为支出，正为收入)：";
		cin >> sum;
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(cin.fail());

	if(sum > 0)
		income = (unsigned long)(sum * 100);
	else
		pay = (unsigned long)(sum * -100);
	cout << "请输入备注:";
	cin >> remark;

	newRecord.initial(date,pay,type,income,remark);
	selectAccount->addRecord(newRecord);
	cout << selectAccount->getName() << "\t余额：" <<selectAccount->getTotalLeft() << endl;
}

void viewCurrentMonth(CMenu** nowMenu)
{
	time_t ltime;
	time(&ltime);
	tm* t;
	t = gmtime(&ltime);
	unsigned long date = getDate(t->tm_year + 1900, t->tm_mon + 1,1); 
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getMonthStartEnd(date,bank_start,bank_end);
	g_cash.getMonthStartEnd(date,cash_start,cash_end);
	g_bank.print(cout,bank_start,bank_end);
	g_cash.print(cout,cash_start,cash_end);
	getchar();
}

void viewSetMonth(CMenu** nowMenu)
{
	if((*nowMenu)->privateData == NULL){ 
		cout << "没有设定时间，请重新设定时间"<< endl;
		getchar();
		return;
	}
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getMonthStartEnd(*(unsigned long*)(*nowMenu)->privateData,bank_start,bank_end);
	g_cash.getMonthStartEnd(*(unsigned long*)(*nowMenu)->privateData,cash_start,cash_end);
	g_bank.print(cout,bank_start,bank_end);
	g_cash.print(cout,cash_start,cash_end);
	getchar();
}

void viewSetDay(CMenu** nowMenu)
{
	if((*nowMenu)->privateData == NULL)
	{
		cout << "没有设定时间，请重新设定时间"<< endl;
		getchar();
		return;
	}
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getDayStartEnd(*(unsigned long*)(*nowMenu)->privateData,bank_start,bank_end);
	g_cash.getDayStartEnd(*(unsigned long*)(*nowMenu)->privateData,cash_start,cash_end);
	g_bank.print(cout,bank_start,bank_end);
	g_cash.print(cout,cash_start,cash_end);
	getchar();
}

void setDate(CMenu** nowMenu)
{
	do{
		string date_string;
		cout << "请输入日期(yyyy-month-day):";
		cin >> date_string;
		if((*nowMenu)->privateData == NULL)
			(*nowMenu)->privateData = new unsigned long;
		*(unsigned long*)(*nowMenu)->privateData = stringToDate(date_string);
	}while(*(unsigned long*)(*nowMenu)->privateData == 0);
}

void viewSetDate(CMenu** nowMenu)
{
	if((*nowMenu)->privateData == NULL)
	{
		cout << "没有设定时间，请重新设定时间"<< endl;
		getchar();
		return;
	}
	cout << dateToString(*(unsigned long*)(*nowMenu)->privateData) << endl;
	getchar();
}
CMenu* initialViewRecord()
{
	CMenu* viewRecord = new CMenu("查看记录");

	CMenu* returnMenu = new CMenu("返回上一级目录",mainQuitFun);
	viewRecord->addSubMenu(returnMenu);

	CMenu* currentRecord = new CMenu("查看当月全部记录",viewCurrentMonth);
	viewRecord->addSubMenu(currentRecord);

	CMenu* setRecord = new CMenu("查看指定时间记录",viewSetMonth);
	viewRecord->addSubMenu(setRecord);

	CMenu* dayRecord = new CMenu("查看某天的记录",viewSetDay);
	viewRecord->addSubMenu(dayRecord);

	CMenu* setDateRecord = new CMenu("设定时间",setDate);
	viewRecord->addSubMenu(setDateRecord);

	CMenu* viewDateRecord = new CMenu("查看设定时间",viewSetDate);
	viewRecord->addSubMenu(viewDateRecord);
	return viewRecord;
}

void save(CMenu** nowMenu)
{
	ofstream out;
	out.open("accountRecord");
	if(out){
		g_bank.save(out);
		g_cash.save(out);
	}
}

CMenu* initialModifyMenu()
{
	CMenu* modifyMenu = new CMenu("修改记录");
	return modifyMenu;
}
CMenu* initialMainMenu()
{
	CMenu* mainMenu = new CMenu("mainMenu");
	CMenu* mainQuit = new CMenu("退出",mainQuitFun);
	mainMenu->addSubMenu(mainQuit);

	CMenu* addRecordMenu = new CMenu("添加记录",addRecord);
	mainMenu->addSubMenu(addRecordMenu);

	mainMenu->addSubMenu(initialViewRecord());

	mainMenu->addSubMenu(initialModifyMenu());

	CMenu* saveMenu = new CMenu("保存",save);
	mainMenu->addSubMenu(saveMenu);
	return mainMenu;
}

int showRecord()
{
	int i = -1;
	do{
		cout << "1、查看当月全部记录"<<endl;
		cout << "2、查看指定时间记录"<<endl;
		cout << "3、查看某天记录"<<endl;
		cout << "4、设定时间"<<endl;
		cout << "0、返回上一级目录"<<endl;
		cout << "请选择菜单:";
		cin >> i;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(i < 0 || i >4);
	return i;
} 

CMenu::CMenu(const string& menuName, menuFun pMenuFun /* = NULL*/)
{
	m_menuName = menuName;
	m_fun = pMenuFun ;
	m_parent = NULL; 
	privateData = NULL;
} 

CMenu::~CMenu()
{
	int subCount = m_subMenu.size();
	if(privateData)
		delete privateData;
	for(int i = 0; i < subCount; i++)
		delete m_subMenu[i];
}

void CMenu::addSubMenu(CMenu* subMenu)
{
	m_subMenu.push_back(subMenu);
	subMenu->setParent(this);
}

void CMenu::delSubMenu(string& subMenuName)
{
	int subCount = m_subMenu.size();
	for(int i = 0; i < subCount ; i++)
	{
		if(subMenuName == m_subMenu[i]->getString())
		{
			delSubMenu(i);
			return;
		}
	}
}

void  CMenu::delSubMenu(int nIndex)
{
	CMenu* pMenu = m_subMenu[nIndex];
	delete pMenu;
	vector<CMenu*>::iterator iter = m_subMenu.begin();
	m_subMenu.erase(iter + nIndex);
}

int CMenu::showSubMenu()
{
	int subCount = m_subMenu.size();
	int select = -1;
	do{
		for(int i = 0; i < subCount; i++)
			cout<<i<<"、 "<<m_subMenu[i]->getString()<<endl;
		cout << "请选择菜单:";
		cin>>select;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(select < 0 || select >= subCount);
	return select;
}

void CMenu::selectSubMenu(int select,CMenu** nowMenu)
{
	int subCount = m_subMenu.size();
	if(select < 0 || select >= subCount)
		return;
	if(m_subMenu[select]->m_subMenu.size() > 0)
		*nowMenu = m_subMenu[select];
	else if(m_subMenu[select]->m_fun)
		m_subMenu[select]->m_fun(nowMenu);
}

