#ifndef ACCOUNT_H_HJC20090409
#define ACCOUNT_H_HJC20090409
#include "record.h"
#include <vector>
#include <fstream>
using namespace std;

class account{
	private:
		vector<record> m_vRecord;
		vector<long>   m_vRecordLeft;
		string m_name;
		long m_initialCash;
		long m_left;
		inline void calculate(const record& newRecord);
	public:
		account();
		account(string name,int initialCash = 0);
		~account();
		void save(ofstream& outFile);
		void load(ifstream& inFile);
		void print(ostream& out);
		void addRecord(const record& newRecord);
		void reCalculate();
		void sortRecord();
		string getName(){ return m_name;};
		float getTotalLeft(){return m_left / 100.f;};
		record getRecordAt(int i){return m_vRecord[i];};
		float getLeftAt(int i){ return m_vRecordLeft[i] / 100.f;};
		void getMonthStartEnd(unsigned long date, int& start, int& end);

};
#endif