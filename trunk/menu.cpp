#include "menu.h"
#include <iostream>
using namespace std;

int showMainMenu()
{
	int i = -1;
	do{
		cout << "1、查看记录"<<endl;
		cout << "2、添加记录"<<endl;
		cout << "0、退出"<<endl;
		cout << "请选择菜单:";
		cin >> i;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}while(i < 0 || i > 2);
	return i;
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
	m_subMenu[select]->m_fun(nowMenu);
}

