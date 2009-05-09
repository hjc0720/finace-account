#include "menu.h"
#include "account.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

account g_bank("银行卡");
account g_cash("现金");

int main()
{
	ifstream infile;
	infile.open("accountRecord");
	if(infile)
	{
		g_bank.load(infile);
		g_cash.load(infile);
	}
	infile.close();
	time_t ltime;
	time(&ltime);
	tm* t;
	t = gmtime(&ltime);
	cout << t->tm_year + 1900<<"-"<<t->tm_mon + 1<<"-"<<t->tm_mday<<endl;

	cout << g_bank.getName() << "\t余额：" <<g_bank.getTotalLeft() << endl;
	cout << g_cash.getName() << "\t余额：" <<g_cash.getTotalLeft() << endl;
	CMenu* mainMenu = initialMainMenu();
	CMenu* nowMenu = mainMenu;
	int select = -1;
	do
	{
		select = nowMenu->showSubMenu();
		nowMenu->selectSubMenu(select,&nowMenu);
	}while(nowMenu);
	delete mainMenu;
//	int select = showMainMenu();
//	while(select != 0)
//	{
//		selectMainMenu(select);
//		select = showMainMenu();
//	}
	ofstream out;
	out.open("accountRecord");
	if(out){
		g_bank.save(out);
		g_cash.save(out);
	}
	return 1;
}

