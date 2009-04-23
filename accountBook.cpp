#include "account.h"
#include <iostream>
#include <fstream>
using namespace std;
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
	return 1;
}

