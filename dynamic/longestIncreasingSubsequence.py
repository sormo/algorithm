# The longest Increasing Subsequence (LIS) problem is to find the length of the
# longest subsequence of a given sequence such that all elements of the subsequence 
# are sorted in increasing order. For example, length of LIS 
# for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}. 
# for { 100, 1, 2, 3, 200} is 3 and LIS is {1, 2, 3}

def LISReconstruct(arr, A, R):
	maxIndex = 0
	maxValue = 0
	for i in range(0, len(A)):
		if A[i] > maxValue:
			maxIndex = i
			maxValue = A[i]

	ret = []
	i = maxIndex
	while(i != -1):
		ret.append(arr[i])
		i = R[i]

	ret.reverse()

	return ret

def longestIncreasingSubsequence(arr):
	# A[i] longest increasing subsequence taking into account first i elements, including i-th element
	#		note that A[i] is the biggest (last) in sequence
	A = [1] * len(arr)
	R = [-1] * len(arr) # store second to last index

	for i in range(1, len(arr)):
		for j in range(0, i):
			# if i-th element is bigger then j-th this is candidate subsequence
			if arr[i] > arr[j]:
				# A[i] = max(m, A[j] + 1)
				if A[j] + 1 > A[i]:
					R[i] = j
					A[i] = A[j] + 1

	print(LISReconstruct(arr, A, R))

	return max(A)

# test 1:
test1 = [10, 22, 9, 33, 21, 50, 41, 60, 80]
print("LIS: " + str(test1) + ": " + str(longestIncreasingSubsequence(test1)) + " = 6")
# test 2:
test2 = [100, 1, 2, 3, 200]
print("LIS: " + str(test2) + ": " + str(longestIncreasingSubsequence(test2)) + " = 4")


# optionaly
# construct tree with edges (i,j) if i < j and A[i] < A[j]
def constructLISTree(arr):
	# TODO can I return structure with named elements ???
	tails = {}
	heads = {}

	# TODO do this in one line
	for i in range(len(arr)):
		tails[i] = []
		heads[i] = []

	for i in range(len(arr)):
		for j in range(i + 1, len(arr)):
			if arr[i] < arr[j]:
				tails[i].append(j)
				heads[j].append(i)

	return (tails, heads)

def computeLISFromTree(arr, tree):
	A = [1 for x in range(len(arr))]

	for i in range(len(arr)):
		# TODO do this in one line
		# for all nodes for which is i head
		for j in tree[1][i]:
			if 1 + A[j] > A[i]:
				A[i] = 1 + A[j]

	return max(A)

print("LIS opt: " + str(test1) + ": " + str(computeLISFromTree(test1, constructLISTree(test1))) + " = 6")
print("LIS opt: " + str(test2) + ": " + str(computeLISFromTree(test2, constructLISTree(test2))) + " = 4")

