//
// Created by scrapy.py on 27.04.2020.
//

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


Number Grade_school::multiply(const Number& a, const Number& b)
{
    Number s1 = a;
    Number s2 = b;

    std::reverse(s1.getStr().begin(), s1.getStr().end());
    std::reverse(s2.getStr().begin(), s2.getStr().end());

    Number result;
    for (size_t i = 0; i < b.size(); i++)
    {
        std::string tmp;
        int carry = 0;
        Number res;
        for (size_t j = 0; j < a.size(); j++)
        {
            tmp = std::to_string(((s1[j] - '0') * (s2[i] - '0')) + carry);
            if (tmp.length() == 2)
            {
                carry = tmp[0] - '0';
                res.push_back(tmp[1]);
            }

            else
            {
                res.getStr() += tmp;
                carry = 0;
            }

        }

        if (carry)
            res.getStr() += std::to_string(carry);

        res.getStr().insert(0, i, '0');
        std::reverse(res.getStr().begin(), res.getStr().end());
        result = result + res;
    }

    return result;
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

