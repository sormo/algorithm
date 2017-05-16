#include "misc.h"
#include "..\common\common.h"

std::string ThirdGradeMultiply(const std::string& a, const std::string & b)
{
	std::vector<char> na = ConvertToDigits(a);
	std::vector<char> nb = ConvertToDigits(b);

	// compute subproducts

	std::vector<std::vector<char>> subproducts;
	int maxSizeSubproduct = 0;

	for (int ib = nb.size() - 1; ib >= 0; ib--)
	{
		char carry = 0;
		std::vector<char> subproduct;

		for (int i = 0; i < (int)nb.size() - 1 - ib; i++)
			subproduct.push_back(0);

		for (int ia = na.size() - 1; ia >= 0; ia--)
		{
			char c = na[ia] * nb[ib];
			c += carry;

			char p = c % 10;
			carry = (c - p) / 10;

			subproduct.push_back(p);
		}

		if (carry)
			subproduct.push_back(carry);

		std::reverse(subproduct.begin(), subproduct.end());
		subproducts.push_back(subproduct);

		maxSizeSubproduct = std::max(maxSizeSubproduct, (int)subproduct.size());
	}

	// add all subproducts together

	std::vector<char> ret;

	char c = 0;
	for (int i = 0; i < maxSizeSubproduct; i++)
	{
		for (const auto & p : subproducts)
		{
			int idx = (int)p.size() - 1 - i;
			if (idx >= 0)
				c += p[idx];
		}

		ret.push_back(c % 10);
		c /= 10;
	}
	if (c)
		ret.push_back(c);

	std::reverse(ret.begin(), ret.end());

	return ConvertFromDigits(ret);
}
