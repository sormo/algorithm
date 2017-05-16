#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

// given dimensions of chain of matrices A, B, C, D return minimum number of operations
// to multiply whole chain like A * B * C * D
// cost of multiplication of two matrices A(x,y) * B(y,z) is x*y*z

void PrintMultiplicationChainRec(size_t i, size_t j, const std::vector<size_t> & dimensions, const std::vector<std::vector<size_t>> & K, std::string & out)
{
	if (i == j)
	{
		out += std::to_string(dimensions[i - 1]) + "x" + std::to_string(dimensions[i]);
		return;
	}

	out.push_back('(');

	PrintMultiplicationChainRec(i, K[i][j], dimensions, K, out);
	PrintMultiplicationChainRec(K[i][j] + 1, j, dimensions, K, out);

	out.push_back(')');
}

std::string PrintMultiplicationChain(const std::vector<size_t> & dimensions, const std::vector<std::vector<size_t>> & K)
{
	std::string ret;
	PrintMultiplicationChainRec(1, dimensions.size() - 1, dimensions, K, ret);
	return ret;
}

// dimensions contains n-1 matrices where i-th matrix has dimension d[i-1]xd[i]
std::tuple<size_t, std::string> MatrixChainMultiplication(const std::vector<size_t> & dimensions)
{
	const size_t N = dimensions.size();
	// A[i][j] - minimum number of operations to multiply chain from i-th to j-th matrix (inclusive) 
	std::vector<std::vector<size_t>> A(N, std::vector<size_t>(N, 0));
	// K[i][j] - auxiliary array to remember bracket position in minimum multiplication of matrices from i to j
	std::vector<std::vector<size_t>> K(N, std::vector<size_t>(N, 0));

	for (size_t L = 2; L < N; ++L) // subproblem size
	{
		for (size_t i = 1; i < N; ++i)
		{
			size_t j = i + L - 1;
			if (j >= N)
				break;

			size_t min = std::numeric_limits<size_t>::max();
			for (size_t k = i; k < j; ++k)
			{
				size_t tmp = A[i][k] + A[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
				if (tmp < min)
				{
					A[i][j] = tmp;
					K[i][j] = k;
				}
			}
		}
	}

	return{ A[1][N - 1], PrintMultiplicationChain(dimensions, K) } ;
}
