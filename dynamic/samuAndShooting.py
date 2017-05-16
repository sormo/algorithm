"""
Samu is playing a shooting game in play station. There are two apples to aim in this shooting game. Hitting first apple will provide her X points and hitting second apple will provide her Y points. And if she misses the apple she chose to hit, she wont get any point.

Now she is having N coins and each shoot will cost her 1 coin and she needs to score at least W points to win the game.

Samu don't like to loose at any cost. At each turn, she has two choices. The choices include:-

    Hitting first apple with probability P1 percent. However, she might miss it with probability (1-P1) percentage.
    Hitting second apple with probability P2 percent. However, she might miss it with probability (1-P2) percentage.

She would like to know what is the maximal expected probability(as a percentage b/w 0 and 100) of winning the shooting game.
"""
def prettyPrint(l):
    for i in range(len(l)):
        s = ""
        for j in range(len(l[i])):
            s += ' {:09.6f}'.format(l[i][j])
        print(s)


def samuAndShooting(x,y,n,w,px,py):
    A = [[0.0 for j in range(n)] for i in range(w)]

    # initialization
    A[x-1][0] = px
    A[y-1][0] = py

    for j in range(1, n):
        for i in range(w):
            # throw to x
            xhit = 0.0
            if i-x >= 0:
                xhit = px*A[i-x][j-1]
            xmiss = (1.0-px)*A[i][j-1]
            # throw to y
            yhit = 0.0
            if i-y >= 0:
                yhit = py*A[i-y][j-1]
            ymiss = (1.0-py)*A[i][j-1]

            A[i][j] = max(xhit+xmiss, yhit+ymiss)

    prettyPrint(A)

    return max(A[w-1])

def samuAndShooting2(x,y,n,w,px,py):
    A = [[-1.0 for j in range(n+1)] for i in range(w+1)]

    ret = samuAndShooting2Rec(x,y,n,w,px,py,A)

    prettyPrint(A)

    return ret

def samuAndShooting2Rec(x,y,n,w,px,py,A):
    if w <= 0:
        A[w][n] = 1.0
        return 1.0
    if n == 0:
        A[w][n] = 0.0
        return 0.0
    if A[w][n] >= 0.0:
        return A[w][n]
    A[w][n] = max( samuAndShooting2Rec(x,y,n-1,w-x,px,py,A)*px + samuAndShooting2Rec(x,y,n-1,w,px,py,A)*(1.0-px),
                   samuAndShooting2Rec(x,y,n-1,w-y,px,py,A)*py + samuAndShooting2Rec(x,y,n-1,w,px,py,A)*(1.0-py) )
    return A[w][n]

print("test1	" + "%.6f" % (samuAndShooting(1,2,4,6,0.50,0.25)*100.0) + "	%.6f" % (samuAndShooting2(1,2,4,6,0.50,0.25)*100.0))
"""
print("test2	" + "%.6f" % (samuAndShooting(5,1,10,5,0.50,0.1)*100.0) + "	%.6f" % (samuAndShooting2(5,1,10,5,0.50,0.1)*100.0))
print("test3	" + "%.6f" % (samuAndShooting(1,5,20,50,0.50,0.1)*100.0) + "	%.6f" % (samuAndShooting2(1,5,20,50,0.50,0.1)*100.0))
print("test4	" + "%.6f" % (samuAndShooting(2,3,95,62,0.5,0.35)*100.0) + "	%.6f" % (samuAndShooting2(2,3,95,62,0.5,0.35)*100.0))
print("test5	" + "%.6f" % (samuAndShooting(2,3,485,205,0.28,0.18)*100.0) + "	%.6f" % (samuAndShooting2(2,3,485,205,0.28,0.18)*100.0))
print("test6	" + "%.6f" % (samuAndShooting(4,8,620,928,0.20,0.27)*100.0) + "	%.6f" % (samuAndShooting2(4,8,620,928,0.20,0.27)*100.0))
print("test7	" + "%.6f" % (samuAndShooting(1,4,314,641,0.91,0.46)*100.0) + "	%.6f" % (samuAndShooting2(1,4,314,641,0.91,0.46)*100.0))
print("test8	" + "%.6f" % (samuAndShooting(1,8,132,792,0.87,0.52)*100.0) + "	%.6f" % (samuAndShooting2(1,8,132,792,0.87,0.52)*100.0))
print("test9	" + "%.6f" % (samuAndShooting(7,5,59,191,0.1,0.52)*100.0) + "	%.6f" % (samuAndShooting2(7,5,59,191,0.1,0.52)*100.0))
print("test10	" + "%.6f" % (samuAndShooting(9,4,287,709,0.24,0.50)*100.0) + "	%.6f" % (samuAndShooting2(9,4,287,709,0.24,0.50)*100.0))
"""