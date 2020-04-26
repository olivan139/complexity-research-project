#include "Multiplicator.h"

Number Multiplicator::generate_random(const size_t& k)
{
	std::string s;

	s.push_back(rand() % 9 + 49);
	for (size_t i = 0; i < k - 1; i++)
	{
		s.push_back((rand() % 10) + 48);
	}

	return Number(s);
}

Number Grade_school::multiply(const Number& frst, const  Number& scnd)
{
	int carry = 0;
	std::string a = "0";
	Number f_result(a);
	for (int i = scnd.size() - 1; i >= 0; i--)
	{
		std::string result = "";
		int sc = scnd[i] - 48;
		for (int j = frst.size() - 1; j >= 0; j--)
		{
			int fst = frst[j] - 48;
			std::string temp2 = std::to_string(sc * fst + carry);
			if (temp2.length() == 2)
			{
				carry = temp2[0] - 48;
				result += temp2[1];
			}
			else
			{
				result += temp2;
				carry = 0;
			}
		}
		if (carry != 0) {
			result += std::to_string(carry);
		}
		std::reverse(result.begin(), result.end());
		for (size_t k = 0; k < scnd.size() - 1 - i; k++)
		{
			result += "0";
		}
		Number temp_res(result);
		f_result = f_result + temp_res;
		carry = 0;
	}
	return f_result;
}



Number D_C::multiply(const Number& a, const Number& b)
{
	Number c = a, d = b;
	size_t n = std::max(a.size(), b.size());

	c.adding_zeros_left(n - c.size());
	d.adding_zeros_left(n - d.size());

	if (n == 1) { return c * d; }

	std::pair<Number, Number> para = c.split(n);
	Number x1 = para.first;
	Number y1 = para.second;

	para = d.split(n);
	Number x2 = para.first;
	Number y2 = para.second;

	n = (n / 2) + (n % 2);

	Number w1 = multiply(x1, x2);
	Number w2 = multiply(x1, y2);
	Number w3 = multiply(y1, x2);
	Number w4 = multiply(y1, y2);

	w1.adding_zeros_right(2 * n);
	w2.adding_zeros_right(n);
	w3.adding_zeros_right(n);

	return w1 + w2 + w3 + w4;
}

Number Karatsuba::multiply(const Number& a, const Number& b)
{
	Number c = a, d = b;
	size_t n = std::max(a.size(), b.size());

	c.adding_zeros_left(n - a.size());
	d.adding_zeros_left(n - b.size());

	if (n == 1) {return c * d;}

	std::pair<Number, Number> para = c.split(n);
	Number x1 = para.first;
	Number y1 = para.second;

	para = d.split(n);
	Number x2 = para.first;
	Number y2 = para.second;

	Number w1 = multiply(y1, y2);
	Number w2 = multiply(x1 + y1, x2 + y2);
	Number w3 = multiply(x1, x2);

	n = (n / 2) + (n % 2);

	w2 = w2 - w1 - w3;

	w3.adding_zeros_right(2 * n);
	w2.adding_zeros_right(n);

	return w1 + w2 + w3;
}
