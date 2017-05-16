#include "recursion.h"
#include "..\common\common.h"

std::vector<char> KaratsubaRecursive(const std::vector<char> & num1, const std::vector<char> & num2)
{
	// base case
	if (num1.size() == 1 || num2.size() == 1)
	{
		const std::vector<char> * one = num1.size() == 1 ? &num1 : &num2;
		const std::vector<char> * other = &num1 == one ? &num2 : &num1;

		std::vector<char> ret = { 0 };
		for (char i = 0; i < one->at(0); i++)
			ret = AddNumbers(ret, *other);

		return ret;
	}

	// recursive case

	size_t m = num1.size() / 2;

	std::vector<char> a(num1.begin(), num1.begin() + m);
	std::vector<char> b(num1.begin() + m, num1.end());
	std::vector<char> c(num2.begin(), num2.begin() + m);
	std::vector<char> d(num2.begin() + m, num2.end());

	std::vector<char> ac = KaratsubaRecursive(a, c);
	std::vector<char> bd = KaratsubaRecursive(b, d);
	std::vector<char> abcd = KaratsubaRecursive(AddNumbers(a,b), AddNumbers(c,d));

	std::vector<char> adplusbc = SubNumbers(SubNumbers(abcd, ac), bd);

	// 10^n
	for (size_t i = 0; i < num1.size(); i++)
		ac.push_back(0);
	// 10^(n/2)
	for (size_t i = 0; i < m; i++)
		adplusbc.push_back(0);

	return AddNumbers(ac, AddNumbers(adplusbc, bd));
}

// both a and b must be same size

std::string KaratsubaMultiply(const std::string& a, const std::string & b)
{
	return ConvertFromDigits(KaratsubaRecursive(ConvertToDigits(a), ConvertToDigits(b)));
}