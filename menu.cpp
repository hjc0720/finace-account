#include "menu.h"
#include <iostream>
#include "account.h"
#include "record.h"
#include "basefunction.h"
using namespace std;
//全局变量
extern account g_bank;
extern account g_cash;
extern string typeString[PayIncomeTypeCount];
unsigned long g_dateShow = 0;
string selectRecordIndex;
	
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

	cout << g_bank.getName() << "\t余额：" <<g_bank.getTotalLeft() << endl;
	g_bank.print(cout,bank_start,bank_end);
	cout << g_cash.getName() << "\t余额：" <<g_cash.getTotalLeft() << endl;
	g_cash.print(cout,cash_start,cash_end);
	getchar();
}

void modifyRecordCurrentMonth(CMenu** nowMenu)
{
	time_t ltime;
	time(&ltime);
	tm* t;
	t = gmtime(&ltime);
	unsigned long date = getDate(t->tm_year + 1900, t->tm_mon + 1,1); 
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getMonthStartEnd(date,bank_start,bank_end);
	g_cash.getMonthStartEnd(date,cash_start,cash_end);
	int nIndex = 1;
	g_bank.print(cout,bank_start,bank_end,&nIndex);
	g_cash.print(cout,cash_start,cash_end,&nIndex);
	cout<<endl;
	int sel = 0,realSel,isCon;
	do{
		cout<<"请选择要修改的记录(输入0为返回):";
		cin >> sel;
		if(sel <= 0 && (bank_end - bank_start + cash_start - cash_end + 2) < sel) return;
		sel--;
		account* selAccount = NULL;
		if(sel <= bank_end - bank_start)
		{
			selAccount = &g_bank;
			realSel = bank_start + sel;
		}
		else 
		{
			selAccount = &g_cash;
			realSel = cash_start + sel - bank_end + bank_start - 1;
		}
		cout << "你选中的记录是:" << endl;
		selAccount->print(cout,realSel,realSel);
		cout <<"确认请按1,重新输入请按2,取消请按0:";
		cin >> isCon;
		if(isCon == 1)
			selAccount->addDelRecordList(realSel);
	}while(isCon == 2);
}

void viewSetMonth(CMenu** nowMenu)
{
	if(g_dateShow == 0){ 
		cout << "没有设定时间，请重新设定时间"<< endl;
		getchar();
		return;
	}
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getMonthStartEnd(g_dateShow ,bank_start,bank_end);
	g_cash.getMonthStartEnd(g_dateShow ,cash_start,cash_end);
	cout << g_bank.getName() << "\t余额：" <<g_bank.getTotalLeft() << endl;
	g_bank.print(cout,bank_start,bank_end);
	cout << g_cash.getName() << "\t余额：" <<g_cash.getTotalLeft() << endl;
	g_cash.print(cout,cash_start,cash_end);
	getchar();
}

void viewSetDay(CMenu** nowMenu)
{
	if(g_dateShow == 0)
	{
		cout << "没有设定时间，请重新设定时间"<< endl;
		getchar();
		return;
	}
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getDayStartEnd(g_dateShow ,bank_start,bank_end);
	g_cash.getDayStartEnd(g_dateShow ,cash_start,cash_end);
	cout << g_bank.getName() << "\t余额：" <<g_bank.getTotalLeft() << endl;
	g_bank.print(cout,bank_start,bank_end);
	cout << g_cash.getName() << "\t余额：" <<g_cash.getTotalLeft() << endl;
	g_cash.print(cout,cash_start,cash_end);
	getchar();
}

void setDate(CMenu** nowMenu)
{
	do{
		string date_string;
		cout << "请输入日期(yyyy-month-day):";
		cin >> date_string;
		g_dateShow = stringToDate(date_string);
	}while(g_dateShow == 0);
}

void viewSetDate(CMenu** nowMenu)
{
	if(g_dateShow == 0)
	{
		cout << "没有设定时间，请重新设定时间"<< endl;
		getchar();
		return;
	}
	cout << dateToString(g_dateShow ) << endl;
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

void viewSelRecord(CMenu** nowMenu)
{
	for(int i = 0; i < g_bank.getDelRecordListCount();i++)
		g_bank.print(cout,g_bank.getDelRecordListAt(i),g_bank.getDelRecordListAt(i));

	for(int i = 0; i < g_cash.getDelRecordListCount();i++)
		g_cash.print(cout,g_cash.getDelRecordListAt(i),g_cash.getDelRecordListAt(i));
}

void delSelRecord(CMenu** nowMenu)
{
	for(int i = 0; i < g_bank.getDelRecordListCount();i++)
		g_bank.delRecord(g_bank.getDelRecordListAt(i));
	for(int i = 0; i < g_cash.getDelRecordListCount();i++)
		g_cash.delRecord(g_cash.getDelRecordListAt(i));
	g_bank.clearRecordList();
	g_cash.clearRecordList();
}

void clearInvalidRecord(CMenu** nowMenu)
{
	g_bank.clearInvalidRecord(cout);
	g_cash.clearInvalidRecord(cout);
}

CMenu* initialModifyMenu()
{
	CMenu* modifyMenu = new CMenu("修改记录");

	CMenu* returnMenu = new CMenu("返回上一级目录",mainQuitFun);
	modifyMenu->addSubMenu(returnMenu);

	CMenu* findRecordMenu = new CMenu("查找记录");
	modifyMenu->addSubMenu(findRecordMenu);

	CMenu* clearInvalid = new CMenu("清除无效记录",clearInvalidRecord);
	modifyMenu->addSubMenu(clearInvalid );

	CMenu* modifyRecordMenu = new CMenu("修改选中的记录");
	modifyMenu->addSubMenu(modifyRecordMenu);

	CMenu* delRecordMenu = new CMenu("删除选中的记录",delSelRecord);
	modifyMenu->addSubMenu(delRecordMenu );

	CMenu* viewSelRecMenu = new CMenu("查看选中的记录",viewSelRecord);
	modifyMenu->addSubMenu(viewSelRecMenu );
//查找记录菜单
	returnMenu = new CMenu("返回上一级目录",mainQuitFun);
	findRecordMenu->addSubMenu(returnMenu);

	CMenu* currentRecord = new CMenu("查看当月全部记录",modifyRecordCurrentMonth);
	findRecordMenu->addSubMenu(currentRecord);

	CMenu* setRecord = new CMenu("查看指定时间记录");
	findRecordMenu->addSubMenu(setRecord);

	CMenu* dayRecord = new CMenu("查看某天的记录");
	findRecordMenu->addSubMenu(dayRecord);

	CMenu* setDateRecord = new CMenu("设定时间");
	findRecordMenu->addSubMenu(setDateRecord);

	CMenu* viewDateRecord = new CMenu("查看设定时间");
	findRecordMenu->addSubMenu(viewDateRecord);

	return modifyMenu;
}

void analy(CMenu** nowMenu)
{
	float bankIncome[PayIncomeTypeCount] = {0},bankPay[PayIncomeTypeCount] = {0};
	float cashIncome[PayIncomeTypeCount] = {0},cashPay[PayIncomeTypeCount] = {0};
	float incomeSum = 0, paySum =0;
	time_t ltime;
	time(&ltime);
	tm* t;
	t = gmtime(&ltime);
	unsigned long date = getDate(t->tm_year + 1900, t->tm_mon + 1,1); 
	int bank_start,bank_end,cash_start,cash_end;
	g_bank.getMonthStartEnd(date,bank_start,bank_end);
	g_cash.getMonthStartEnd(date,cash_start,cash_end);
	for(int i = bank_start; i <= bank_end; i++)
	{
		int nType = g_bank.getRecordAt(i).GetType();
		bankIncome[nType] += g_bank.getRecordAt(i).GetIncome() /100.f;
		bankPay[nType] += g_bank.getRecordAt(i).GetPay() /100.f;
	}
	for(int i = cash_start; i <= cash_end; i++)
	{
		int nType = g_cash.getRecordAt(i).GetType();
		cashIncome[nType] += g_cash.getRecordAt(i).GetIncome() /100.f;
		cashPay[nType] += g_cash.getRecordAt(i).GetPay()/ 100.f;
	}
	cout<<getYear(date)<<"年"<<getMonth(date)<<"月,支出分析:"<<endl;
	for(int i = 0; i < PayIncomeTypeCount; i++)
	{
		if(bankPay[i] + cashPay[i] == 0)
			continue;
		//cout<<g_bank.getName()<<"\t"<<typeString[i]<<"总支出\t"<<bankPay[i]<<endl;
		//cout<<g_cash.getName()<<"\t"<<typeString[i]<<"总支出\t"<<cashPay[i]<<endl;
		cout<<typeString[i]<<"总支出\t"<<cashPay[i] + bankPay[i]<<endl;
		paySum += bankPay[i] + cashPay[i];
	}
	cout<<getYear(date)<<"年"<<getMonth(date)<<"月,收入分析:"<<endl;
	for(int i = 0; i < PayIncomeTypeCount; i++)
	{
		if(bankIncome[i] + cashIncome[i] == 0)
			continue;
//		cout<<g_bank.getName()<<"\t"<<typeString[i]<<"总收入\t"<<bankIncome[i]<<endl;
	//	cout<<g_cash.getName()<<"\t"<<typeString[i]<<"总收入\t"<<cashIncome[i]<<endl;
		cout<<typeString[i]<<"总收入\t"<<cashIncome[i] + bankIncome[i]<<endl;
		incomeSum += bankIncome[i] + cashIncome[i];
	}
	cout<<"本月总支出:"<<paySum<<endl;
	cout<<"本月总收入:"<<incomeSum<<endl;;
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

	CMenu* analyMenu = new CMenu("收支分析",analy);
	mainMenu->addSubMenu(analyMenu);

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
} 

CMenu::~CMenu()
{
	int subCount = m_subMenu.size();
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

