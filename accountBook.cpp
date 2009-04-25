#include "menu.h"
#include "account.h"
#include <iostream>
#include <fstream>
using namespace std;
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
	account bank("银行卡");
	account cash("现金");
	ifstream infile;
	infile.open("accountRecord");
	if(infile)
	{
		bank.load(infile);
		cash.load(infile);
	}
	cout << bank.getName() << "\t余额：" <<bank.getLeft() << endl;
	cout << cash.getName() << "\t余额：" <<cash.getLeft() << endl;
	int select = showMainMenu();
	while(select != 0)
	{
		selectMainMenu(select);
		select = showMainMenu();
	}
	return 1;
}

