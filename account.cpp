#include "account.h"
#include <algorithm>

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
		calculate(loadRecord);
	}
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
