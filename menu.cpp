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
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(i < 1 || i > 2);
	return i;
}

int showRecord()
{
	int i = 0;
	do{
		cout << "1、查看当月全部记录";
		cout << "2、查看指定时间记录";
		cout << "3、查看某天记录";
		cout << "4、设定时间";
		cout << "请选择菜单:";
		cin >> i;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(i < 1 || i >4);
	return i;
} 
