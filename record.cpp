#include "record.h"
#include <fstream>
#include <iostream>
#include "basefunction.h"


using namespace std;

string typeString[PayIncomeTypeCount] = 
{
	"老婆给的",
	"卡里取的",
	"工资奖金",
	"生活用品",
	"日常饮食",
	"餐馆消费",
	"商场消费",
	"通讯费用",
	"取出现金",
	"给老婆钱",
	"化妆品",
	"交通费用"

};

record::record()
{
	m_remark.clear();
}

record::~record()
{
}

void record::initial(unsigned long date, unsigned long pay, unsigned char type,unsigned long income, const string& remark)
{
	m_date = date;
	m_pay = pay;
	m_type = type;
	m_remark = remark;
	m_income = income;
}

void record::save(ofstream& outFile)
{
	int nSize = m_remark.size();
	outFile.write((char*)&m_date,sizeof(unsigned long));
	outFile.write((char*)&m_income,sizeof(long));
	outFile.write((char*)&m_pay,sizeof(long));
	outFile.write((char*)&m_type,sizeof(unsigned char));
	outFile.write((char*)&nSize,sizeof(int));
	outFile << m_remark;
}

void record::load(ifstream& inFile)
{
	inFile.read((char*)&m_date,sizeof(unsigned long));
	inFile.read((char*)&m_income,sizeof(long));
	inFile.read((char*)&m_pay,sizeof(long));
	inFile.read((char*)&m_type,sizeof(unsigned char));
	int stringSize;
	inFile.read((char*)&stringSize,sizeof(int));
	char* readString = new char[stringSize + 1];
	inFile.read(readString,stringSize);
//	readString[stringSize] = '\0';
	m_remark.clear();
	m_remark.append(readString,stringSize);
	delete []readString;
}

void record::print(ostream& out)
{
	out << dateToString(m_date)<< '\t';
	out << typeString[m_type] << "\t";
	out << m_pay / 100.f << '\t';
	out << m_income / 100.f<< '\t';
	out << m_remark ;
}

bool record::operator<(record const & rhs) const
{
	if(m_date < rhs.m_date)
		return true;
	return false;
}
