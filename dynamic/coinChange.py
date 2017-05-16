# Given a value N, if we want to make change for N cents, and we have infinite 
# supply of each of S = { S1, S2, .. , Sm} valued coins, how many ways can 
# we make the change? The order of coins doesn't matter.

# For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. 
# So output should be 4. For N = 10 and S = {2, 5, 3, 6}, there are five 
# solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.

# http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/

import sys

####################################################################################################
# classic DP solution
def coinChange(coins, value):
	# A[i][j] = number of ways to sum to j including first i coins
	A = [[0 for y in range(value + 1)] for y in range(len(coins))]

	# initialization
	# if asking for value 0, always there is one way (this is base case)
	# in recursive naive algorithm this one was when subtracted to zero (valid path in recursion tree)
	for i in range(len(coins)):
		A[i][0] = 1

	for i in range(0, len(coins)):
		for j in range(1, value + 1):
			excludingCoin = 0
			includingCoin = 0
			# excluding i-th coin
			# number of ways using first i-1 coins to sum to j
			if i > 0:
				excludingCoin = A[i-1][j]
			# including i-th coin
			# number of ways using first i coins to sum to j - value of i-th coin
			if j - coins[i] >= 0:
				includingCoin = A[i][j - coins[i]]

			# number of ways to sum value j using first i coins
			A[i][j] = includingCoin + excludingCoin

	return A[len(coins)-1][value]

####################################################################################################
# naive recursion
def coinChangeRecursion(coins, value):
	if value == 0:
		return 1
	if value < 0:
		return 0
	if len(coins) == 0:
		return 0
	return coinChangeRecursion(coins[:len(coins)-1], value) + coinChangeRecursion(coins, value - coins[len(coins)-1])

####################################################################################################
# DP with reconstruction
def coinChangeReconstruct(coins, value):
	A = [[0 for y in range(value + 1)] for y in range(len(coins))]

	for i in range(len(coins)):
		A[i][0] = 1

	for i in range(0, len(coins)):
		for j in range(1, value + 1):
			exc = A[i-1][j] if (i > 0) else 0
			inc = A[i][j - coins[i]] if (j - coins[i] >= 0) else 0
			A[i][j] = exc + inc

	# reconstruct from A
	def reconstruct(A, current, total, coinIndex, coins, value):
		if value == 0:
			total.append(current)
			return
		if coinIndex != 0:
			reconstruct(A, current, total, coinIndex - 1, coins, value)
		if value - coins[coinIndex] >= 0:
			tmp = current[:]
			tmp.append(coins[coinIndex])
			reconstruct(A, tmp, total, coinIndex, coins, value - coins[coinIndex])

	ret = []
	reconstruct(A, [], ret, len(coins)-1, coins, value)

	return ret

# test 1
print("test1: " + str(coinChange([1,3,5], 6)) + " = ")
print("test2: " + str(coinChange([1,2], 3)) + " = ")
print("test3: " + str(coinChange([1,2,3], 4)) + " = 4")
print("test3 recursion: " + str(coinChangeRecursion([1,2,3], 4)) + " = 4")
print("test4: " + str(coinChangeReconstruct([1,2,3], 4)) + " = ")