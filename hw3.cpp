#include<iostream>

class Date
{
private:
	int day;
	int month;
	int year;
	void Normalize()
	{
		//create an array of maximum days in each month
		int MaxDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


		//month check
		if (month > 12)
		{
			year += (month - 1) / 12;
			month = (month - 1) % 12 + 1;
		}
		else if (month < 1)
		{
			int yearsToSubtract = (-month + 11) / 12;
			year -= yearsToSubtract;
			month = 12 - (-month + 11) % 12;
		}

		//leap year check
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
		{
			MaxDay[1] = 29;
		}
		else
		{
			MaxDay[1] = 28;
		}

		//proccess the date if the day is greater than the maximum day of the current month

		while (day > MaxDay[month - 1])
		{
			day -= MaxDay[month - 1];
			month++;
			if (month > 12)
			{
				month = 1;
				year++;
			}
		}

		//process the date in case of inserting a day less than or equal to 0
		while (day <= 0)
		{
			month--;
			if (month < 1)
			{
				month = 12;
				year--;
			}
			day += MaxDay[month - 1];
		}
	}


public:

	Date(int d, int m, int y);

	Date() = default;
	int GetDays() const;
	int GetMonths() const;
	int GetYears() const;
	Date(int d) :Date(d, 0, 0) {}

	//leap year
	bool isLeapYear()
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			std::cout << "Leap year!" << "\n";
			return true;

		}
		else
		{
			std::cout << "Isn't Leap year!" << "\n";
			return false;
		}
	}


	//operator overloading +=
	Date& operator+= (int d)
	{
		day += d;
		Normalize();
		return *this;
	}

	//operator overloading +
	Date operator+ (int d) const
	{
		return Date(day + d, month, year);
	}

	//add days
	void AddDays(int d)
	{
		day += d;
		Normalize();
	}

	//operator overloading -
	Date operator- (int d) const
	{
		return Date(day - d, month, year);
	}

	//subtract days
	void Subtract(int d)
	{
		day -= d;
		Normalize();
	}

};



int Date::GetDays() const
{
	return day;
}
int Date::GetMonths() const
{
	return month;
}
int Date::GetYears() const
{
	return year;
}


Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
	Normalize();

}

//operator overloading <<
std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.GetDays() << ":" << date.GetMonths() << ":" << date.GetYears();
	return out;
}

//operator overloading >>
std::istream& operator>>(std::istream& in, Date& date)
{
	int d;
	int m;
	int y;
	char ch;
	in >> d >> ch;
	in >> m >> ch;
	in >> y >> ch;
	date = Date(d, m, y);
	return in;

}


int main()
{

	Date d(40, 11, 2001);
	std::cout << d.GetDays() << "." << d.GetMonths() << "." << d.GetYears() << std::endl;
	d.AddDays(10);
	std::cout << d << std::endl;

	Date d1(19, 02, 2000);
	std::cout << "DATE->" << d1 << std::endl;
	d1.isLeapYear();


	Date x(30, 0, 0);

	std::cout << x.GetDays() << "." << x.GetMonths() << "." << x.GetYears() << std::endl;
	////x.isLeapYear(); 


	return 0;
}