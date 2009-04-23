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
	return 1;
}

