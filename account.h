#ifndef ACCOUNT_H_HJC20090409
#define ACCOUNT_H_HJC20090409
#include "record.h"
#include <vector>
using namespace std;

class account{
	private:
		vector<record> m_vRecord;
		string m_name;
		unsigned long m_initialCash;
	public:
		account();
		account(string name,int initialCash);
		~account();
		void save(ofstream& outFile);
		void load(ifstream& inFile);
		void print(ostream& out);
};
#endif
