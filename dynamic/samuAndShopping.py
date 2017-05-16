# Samu is in super market and in a mood to do a lot of shopping. She needs to 
# buy shirts, pants and shoes for herself and her family. There are N different 
# shops. Each shop contains all these three items but at different prices. Now 
# Samu has a strategy that she won't buy the same item from the current shop 
# if she had already bought that item from the shop adjacent to the current shop.

# Now Samu is confused, because although she want to follow her strategy strictly 
# but at the same time she want to minimize the total money she spends on shopping. 
# Being a good programmer, she asks for your help.

# You are provided description about all N shops i.e costs of all three items in 
# each shop. You need to help Samu find minimum money that she needs to spend such 
# that she buys exactly one item from every shop.

# Input Format:
# First line contain number of test cases T. Each test case in its first line contain 
# N denoting the number of shops in Super Market. Then each of next N lines contains 
# three space separated integers denoting cost of shirts, pants and shoes in that 
# particular shop.

# Output Format:
# For each test case, output the minimum cost of shopping taking the mentioned conditions 
# into account in a separate line.

def samuAndShopping(shops):
    A = [ [0 for y in range(3)] for x in range(len(shops)) ]

    A[0] = shops[0]

    for i in range(1, len(shops)):
        A[i][0] = shops[i][0] + min(A[i-1][1], A[i-1][2])
        A[i][1] = shops[i][1] + min(A[i-1][0], A[i-1][2])
        A[i][2] = shops[i][2] + min(A[i-1][0], A[i-1][1])

    return min(A[len(shops)-1])

test1 = [ [1, 50, 50], [50, 50, 50], [1, 50, 50] ]
print('test1 ' + str(samuAndShopping(test1)) + ' = 52')