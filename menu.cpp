#include "menu.h"
#include <iostream>
using namespace std;

int showMainMenu()
{
	int i = 0;
	do{
		cout << "1、查看记录"<<endl;
		cout << "2、添加记录"<<endl;
		cout << "请选择菜单:";
		cin >> i;
	}while(i < 1 && i > 2);
	return i;
}

