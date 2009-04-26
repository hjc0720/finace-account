#ifndef MENUTEST_HJC_20090424
#define MENUTEST_HJC_20090424
#include <string>
#include <vector>
using namespace std;
class CMenu;
typedef void (*menuFun)(CMenu**);
int showMainMenu();

int showRecord();
//extern CMenu g_mainMenu("mainMenu");
CMenu* initialMainMenu();
class CMenu
{
	public:
		CMenu(const string& menuName,menuFun pMenuFun = NULL);
		~CMenu();
		void addSubMenu(CMenu* subMenu);
		void delSubMenu(string& subMenuName);
		void delSubMenu(int nIndex);
		int showSubMenu();
		void selectSubMenu(int select, CMenu** nowMenu);
		const string& getString()const {return m_menuName;};
		void setParent(CMenu* parent){m_parent = parent;};
		CMenu* getParent(){return m_parent;};
		menuFun m_fun;
	private:
		string m_menuName;
		vector<CMenu*> m_subMenu;
		CMenu* m_parent;
};


#endif
