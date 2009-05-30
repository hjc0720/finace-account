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
		unsigned long m_startDate;
		unsigned long m_endDate;
		unsigned long m_setDate;
		vector<int> m_vDeleteRecordList;
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
		void getDayStartEnd(unsigned long date, int& start, int& end);
		void print(ostream& out,int start, int end, int* startIndex = NULL);
		void setDate(unsigned long date){m_setDate = date;};
		unsigned long getSetDate(){return m_setDate;};
		void setStartDate(unsigned long date){ m_startDate = date;};
		void setEndDate(unsigned long date){ m_endDate = date;};
		unsigned long getStartDate(){return m_startDate;};
		unsigned long getEndDate(){return m_endDate;};
		void addDelRecordList(int i){m_vDeleteRecordList.push_back(i);};
		void delDelRecordList(int i);
		int getDelRecordListCount(){return m_vDeleteRecordList.size();};
		int getDelRecordListAt(int i){return m_vDeleteRecordList[i];}
		void delRecord(int i);
		void clearInvalidRecord(ostream& out);
		void clearRecordList(){m_vDeleteRecordList.clear(); };
};
#endif
