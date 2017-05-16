# Given two sequences, find the length of longest subsequence present in both 
# of them. A subsequence is a sequence that appears in the same relative order, 
# but not necessarily contiguous. 
# For example, "abc", "abg", "bdf", "aeg", "acefg", .. etc are subsequences of "abcdefg".
# So a string of length n has 2^n different possible subsequences.

# subproblems:
# 1: if characters at (i,j) match then A[i][j] = 1 + A[i-1][j-1]
# 2: if characters at (i,j) do not match then A[i][j] = max(A[i-1][j], A[i][j-1])

def longestCommonSubsequence(str1, str2):
	# A[i][j] = largest common subsequence considering first i, j characters (1-based)
	A = [[0 for x in range(len(str2) + 1)] for y in range(len(str1) + 1)]

	# initialization (initialized to 0s)

	for i in range(1, len(str1) + 1):
		for j in range(1, len(str2) + 1):
			if str1[i-1] == str2[j-1]: # -1 because number of characters (index to A) is 1-based
				A[i][j] = 1 + A[i-1][j-1]
			else:
				A[i][j] = max(A[i][j-1], A[i-1][j])

	return A[len(str1)][len(str2)]

# test1:
print("LCS for AGGTAB and GXTXAYB : " + str(longestCommonSubsequence("AGGTAB", "GXTXAYB")) + " = 4")