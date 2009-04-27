#include "menu.h"
#include "account.h"
#include <iostream>
#include <fstream>
using namespace std;

account g_bank("银行卡");
account g_cash("现金");

void selectMainMenu(int select)
{
	int subSelect = -1;
	do{
		switch(select)
		{
			case 1:
				subSelect = showRecord();
				break;
			default:
				subSelect = 0;
				break;
		}
	}while(subSelect != 0);
}
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
	cout << g_bank.getName() << "\t余额：" <<g_bank.getLeft() << endl;
	cout << g_cash.getName() << "\t余额：" <<g_cash.getLeft() << endl;
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

