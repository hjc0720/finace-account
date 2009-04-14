#include "record.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	record test;
	string str;
	cin >> str;
	test.initial(1,1,1,1,str);
	//ofstream infile("test");
	ifstream outfile("test");
	//test.save(infile);
	test.load(outfile);
	outfile.close();
	test.print();
	return 1;
}

