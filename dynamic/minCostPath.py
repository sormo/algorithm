# Given a cost matrix cost[][] and a position (m, n) in cost[][], write a function 
# that returns cost of minimum cost path to reach (m, n) from (0, 0). Each cell 
# of the matrix represents a cost to traverse through that cell. Total cost of 
# a path to reach (m, n) is sum of all the costs on that path (including both source 
# and destination). You can only traverse down, right and diagonally lower cells 
# from a given cell, i.e., from a given cell (i, j), cells (i+1, j), (i, j+1) and (i+1, j+1) 
# can be traversed. You may assume that all costs are positive integers.

# http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/

def minCostPath(matrix):
	A = [[0 for j in range(len(matrix[0]))] for i in range(len(matrix))]

	# initialization
	A[0][0] = matrix[0][0]
	for i in range(1,len(matrix)):
		A[i][0] = matrix[i][0] + A[i-1][0]
	for j in range(1,len(matrix[0])):
		A[0][j] = matrix[0][j] + A[0][j-1]

	for i in range(1, len(matrix)):
		for j in range(1, len(matrix[i])):
			A[i][j] = min(A[i-1][j], A[i][j-1], A[i-1][j-1]) + matrix[i][j]

	return A[len(matrix)-1][len(matrix[0])-1]

test1 = [[1,2,3],
         [4,8,2],
         [1,5,3]]

print("MinCostPath test1: " + str(minCostPath(test1)) + " = 8")
