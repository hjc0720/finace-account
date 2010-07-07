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
	GetCash,
	GiveToWife,
	Cosmetics,
	Traffic,
        PayForMedical,
        PayForElectricWatergas,
        PayForEntainment,
	PayIncomeTypeCount,
};

class record
{
	private:
		unsigned long m_date;
		unsigned long m_pay;
		unsigned long m_income;
		string m_remark;
		unsigned char m_type;
	public:
		record();
		~record();

		void initial(unsigned long date, unsigned long pay, unsigned char type,unsigned long income, const string& remark);
		void save(ofstream& outFile);
		void load(ifstream& inFile);
		void print(ostream& out);
		long GetIncome()const{return m_income;};
		long GetPay() const {return m_pay;};
		inline unsigned char GetType() const {return m_type;};
		inline unsigned long GetDate(){return m_date;};
                string GetRemark(){return m_remark;};
		bool operator<( record const& rhs) const;
};
#endif
