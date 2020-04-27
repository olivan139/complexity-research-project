#include "Number.h"

Number::Number() {}

Number::Number(const std::string& a)
{
	dg = a;
}

Number::Number(const Number& a)
{
	dg = a.dg;
}

Number::~Number() {}
	
std::pair<Number, Number> Number::split(int n) const
{
	unsigned part = (n / 2);

	Number a = dg.substr(0, part),
	b = dg.substr(part, n - part);

	return std::make_pair(a, b);
}

Number& Number::adding_zeros_left(const size_t& n)
{
	std::string zeros(n, '0');
	dg = zeros + dg;
	return *this;
}

Number& Number::adding_zeros_right(const size_t& n)
{
	std::string zeros(n, '0');
	dg = dg + zeros;
	return *this;
}

Number& Number::push_front(const char& el)
{
	dg.insert(0, 1, el);
	return *this;
}

Number& Number::push_back(const char& el)
{
	dg.push_back(el);
	return *this;
}

Number Number::operator +(const Number& numb2) const
{
	Number num1 = dg, num2 = numb2;
	if (num1.size() > num2.size())
		swap(num1.getStr(), num2.getStr());

	Number result;

	int n1 = num1.size(),
		n2 = num2.size();

	reverse(num1.getStr().begin(), num1.getStr().end());
	reverse(num2.getStr().begin(), num2.getStr().end());
	int carry = 0;

	for (size_t i = 0; i < n1; i++)
	{
		int sum = ((num1[i] - 48) + (num2[i] - 48) + carry);
		result.push_back(sum % 10 + 48);
		carry = sum / 10;
	}

	for (size_t i = n1; i < n2; i++)
	{
		int sum = ((num2[i] - 48) + carry);
		result.push_back(sum % 10 + 48);
		carry = sum / 10;
	}

	if (carry)
		result.push_back(carry + 48);

	for (int i = result.size() - 1; i > 0; i--)
	{
		if (result[i] == '0')
			result.getStr().pop_back();
		else
			break;
	}

	std::reverse(result.getStr().begin(), result.getStr().end());
	return result;
}

Number Number::operator - (const Number& numb2) const
{
	Number frst = dg,
	scnd = numb2, res;

	int n1 = frst.size(), n2 = scnd.size();

	std::reverse(frst.getStr().begin(), frst.getStr().end());
	std::reverse(scnd.getStr().begin(), scnd.getStr().end());

	int carry = 0;
	for (int i = 0; i < n2; i++)
	{

		int dif = ((frst[i] - 48) - (scnd[i] - 48) - carry);
		if (dif < 0)
		{
			dif += 10;
			carry = 1;
		}
		else
			carry = 0;

		res.push_back(dif + 48);
	}
	for (int i = n2; i < n1; i++)
	{
		int sub = ((frst[i] - 48) - carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		res.push_back(sub + 48);
	}

	for (size_t i = res.size() - 1; i > 0; --i)
	{
		if (res[i] == '0')
			res.getStr().pop_back();
		else
			break;
	}

	std::reverse(res.getStr().begin(), res.getStr().end());

	return res;
}



Number Number::operator *(const Number& scnd) const
{
	int a, b;
	a = std::stoi(dg);
	b = std::stoi(scnd.dg);
	std::string s = table[a][b];
	Number res(s);
	return res;
}

size_t Number::size() const
{
	return dg.size();
}

char Number::operator [] (size_t i) const
{
	return dg[i];
}

char& Number::operator [] (size_t i)
{
	return dg[i];
}

std::string& Number::getStr()
{
	return dg;
}

std::string Number::getStr() const
{
	return dg;
}

bool operator == (const Number& a, const Number& b)
{
	return (a.dg == b.dg);
}

std::ostream& operator << (std::ostream& out, const Number& res)
{
	out << res.dg;
	return out;
}
std::vector<std::vector<std::string>> Number::table = {
		{"0","0","0","0","0","0","0","0","0","0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
		{"0", "2", "4", "6", "8", "10", "12", "14", "16", "18"},
		{"0", "3", "6", "9", "12", "15", "18", "21", "24", "27"},
		{"0", "4", "8", "12", "16", "20", "24", "28", "32", "36"},
		{"0", "5", "10", "15", "20", "25", "30", "35", "40", "45"},
		{"0", "6", "12", "18", "24", "30", "36", "42", "48", "54"},
		{"0", "7", "14", "21", "28", "35", "42", "49", "56", "63"},
		{"0", "8", "16", "24", "32", "40", "48", "56", "64", "72"},
		{"0", "9", "18", "27", "36", "45", "54", "63", "72", "81"}
};