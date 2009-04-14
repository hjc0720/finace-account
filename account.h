#ifndef ACCOUNT_H_HJC20090409
#define ACCOUNT_H_HJC20090409
#include "record.h"
#include <vector>
#include <fstream>
using namespace std;

class account{
	private:
		vector<record> m_vRecord;
		string m_name;
		long m_initialCash;
		long m_left;
		void calculate(record& newRecord);
	public:
		account();
		account(string name,int initialCash);
		~account();
		void save(ofstream& outFile);
		void load(ifstream& inFile);
		void print(ostream& out);
};
#endif
