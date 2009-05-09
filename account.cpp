#include "account.h"
#include <algorithm>
#include "basefunction.h"

account::account()
{
	m_initialCash = 0;
	m_left = m_initialCash;
}

account::~account()
{
}

account::account(string name, int initialCash/*= 0*/)
{
	m_name = name;
	m_initialCash = initialCash;
	m_left = m_initialCash;
	m_endDate = m_startDate = m_setDate = 0;
}

void account::save(ofstream& outFile)
{
	int nameSize = m_name.size();
	outFile.write((char*)&nameSize,sizeof(int));
	outFile << m_name;
	outFile.write((char*)&m_initialCash,sizeof(long ));
	int recordCount = m_vRecord.size();
	outFile.write((char*)&recordCount ,sizeof(int));
	for(int i = 0; i < recordCount; i++)
		m_vRecord[i].save(outFile);
}

void account::load(ifstream& inFile)
{
	int nameSize;
	inFile.read((char*)&nameSize,sizeof(int));
	char* readString = new char[nameSize];
	inFile.read(readString ,nameSize);
	m_name.clear();
	m_name.append(readString,nameSize);
	delete []readString;
	inFile.read((char*)&m_initialCash,sizeof(long ));
	m_left = m_initialCash;

	int recordCount;
	inFile.read((char*)&recordCount ,sizeof(int));
	m_vRecord.clear();
	for(int i = 0; i < recordCount; i++)
	{
		record loadRecord;
		loadRecord.load(inFile);
		m_vRecord.push_back(loadRecord);
	}
	reCalculate();
}

void account::print(ostream& out)
{
	out << m_name << endl;

	for(unsigned i = 0; i < m_vRecord.size();i++)
	{
		m_vRecord[i].print(out);
		out << m_vRecordLeft[i] <<endl;
	}
}

void account::calculate(const record& newRecord)
{
	m_left = m_left + newRecord.GetIncome() - newRecord.GetPay();
}

void account::addRecord(const record& newRecord)
{
	m_vRecord.push_back(newRecord);
	sortRecord();
}

void account::reCalculate()
{
	m_left = m_initialCash;
	m_vRecordLeft.clear();
	for(unsigned int i = 0; i < m_vRecord.size(); i++)
	{
		calculate(m_vRecord[i]);
		m_vRecordLeft.push_back(m_left);
	}
}

void account::sortRecord()
{
	sort(m_vRecord.begin(),m_vRecord.end());
	reCalculate();
}

void account::getDayStartEnd(unsigned long date, int& start, int& end)
{
	int nCount = m_vRecord.size(),i;
	for( i = 0; i < nCount; i++)
	{
		if(m_vRecord[i].GetDate() == date)
			break;
	}
	start = i;
	for(; i < nCount; i++)
	{
		if(m_vRecord[i].GetDate() != date)
			break;
	}
	end = --i;
}
void account::getMonthStartEnd(unsigned long date, int& start, int& end)
{
	unsigned long year,month;
	year = getYear(date);
	month = getMonth(date);
	unsigned long startDate = getDate(year,month,1);
	unsigned long endDate = getDate(year,month+1,1);
//	reCalculate();
	int nCount = m_vRecord.size(),i;
	for(i = 0; i < nCount; i++)
	{
		if(m_vRecord[i].GetDate() >= startDate)
			break;
	}
	start = i;
	for(;i < nCount; i++)
	{
		if(m_vRecord[i].GetDate() >= endDate)
			break;
	}
	end = --i;
}

void account::print(ostream& out,int start, int end,int* startIndex/* = NULL*/)
{
//	out << getName() << "\t余额：" <<getTotalLeft() << endl;
	for(int i = start; i <= end; i++)
	{
		if(startIndex)
			out << (*startIndex)++<<'\t';
		getRecordAt(i).print(out);
		out <<'\t'<< getLeftAt(i)<<endl;
	}
}

void account::delDelRecordList(int i)
{
	vector<int>::iterator pos = m_vDeleteRecordList.begin() + i;
	m_vDeleteRecordList.erase(pos);
}

void account::delRecord(int i)
{
	vector<record>::iterator pos = m_vRecord.begin() + i;
	m_vRecord.erase(pos);

	vector<long>::iterator lpos = m_vRecordLeft.begin() + i;
	m_vRecordLeft.erase(lpos);
}

void account::clearInvalidRecord()
{
	record temp;
	for(unsigned int i = 0; i < m_vRecord.size();i++)
	{
		if(m_vRecord[i].GetIncome() == 0 && m_vRecord[i].GetPay() == 0)
			delRecord(i);
	}
}
