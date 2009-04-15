#ifndef RECORD_H_HJC20090409
#define RECORD_H_HJC20090409
#include <string>
using namespace std;

enum payIncomeType{
	GetFromWife,
	GetFromCard,
	Salary,
	PayForAccessory,
	PayForEat,
	PayForRestaurant,
	PayForClothes,
	PayForComunicate,
};

class record
{
	private:
		unsigned long m_date;
		long m_pay;
		long m_income;
		unsigned char m_type;
		string m_remark;
	public:
		record();
		~record();
		void initial(unsigned long date, long pay, unsigned char type, long income, const string& remark);
		void save(ofstream& outFile);
		void load(ifstream& inFile);
		void print(ostream& out);
		long GetIncome()const{return m_income;};
		long GetPay() const {return m_pay;};
		bool operator<( record const& rhs) const;
};
#endif
