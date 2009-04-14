#include "account.h"
account::account()
{
	m_initialCash = 0;
}

account::~account()
{
}

account::account(string name, int initialCash)
{
	m_name = name;
	m_initialCash = initialCash;
}

void account::save(ofstream& outFile)
{
}

void account::load(ifstream& inFile)
{
}

void account::print(ostream& out)
{
}
