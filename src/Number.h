#ifndef ADS_NUMBER_H
#define ADS_NUMBER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
class Number
{

public:

	Number();
	Number(const std::string& a);
	Number(const Number& a);
	~Number();

	std::pair<Number, Number> split(int n) const;

	Number& adding_zeros_left(const size_t& n);
	Number& adding_zeros_right(const size_t& n);

	Number& push_front(const char& el);
	Number& push_back(const char& el);

	Number operator +(const Number& scnd) const;
	Number operator - (const Number& numb2) const;
	Number operator *(const Number& scnd) const;

	size_t size() const;

	char operator [] (size_t i) const;
	char& operator [] (size_t i);

	std::string& getStr();
	std::string getStr() const;


	friend std::ostream& operator << (std::ostream& out, const Number& res);
	friend bool operator == (const Number& a, const Number& b);

private:

	std::string dg;
	static std::vector<std::vector<std::string>> table;
};

#endif //ADS_NUMBER_H