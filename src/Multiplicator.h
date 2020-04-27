#pragma once

#include "Number.h"
#include <ctime>

class Multiplicator
{
public:

	virtual Number multiply(const Number& a, const Number& b) = 0;
	
	static Number generate_random(const size_t& k);

	virtual ~Multiplicator() {}
};

class Grade_school : public Multiplicator
{
	Number multiply(const Number& a, const Number& b) override;
};

class D_C : public Multiplicator
{
	Number multiply(const Number& a, const Number& b) override;
};

class Karatsuba : public Multiplicator
{
	Number multiply(const Number& a, const Number& b) override;
};

