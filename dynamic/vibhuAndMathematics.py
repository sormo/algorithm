"""
In code world all genders are considered equal ( It means their is nothing like male or female). Now their are N distinct persons living in this hypothetical world. Each person can pair up with any other person or can even remain single.
One day Vbhu planned to visit code world. Being a maths guy , he always try to be mathematical. So he started counting the ways in which N persons living in code world can make pairs or remain single. A single person can make pair with at most one other person.
Seeing that N can be large , Vibhu ask you for help. Now being a great programmer you need to help Vbhu count the number of ways in which N persons living in code world can make pairs or remain single. 
"""

def vibhuAndMathematics(n):
    A = [None]*(n+1)
    
    A[0] = 1
    A[1] = 1

    for i in range(2, n + 1):
        # A[i-1] -> number of ways when i-th person remain single
        # (i-1) * A[i-2] -> (number of pairs i-th person can create) * number of ways the rest fills in
        A[i] = A[i-1] + (i-1)*A[i-2]

    print(A)

    return A[n]

print("test1 " + str(vibhuAndMathematics(3)) + " = 4")

###

def vibhuAndMathematics2(nset):
	modulo = 10**9 + 7
	tmp = {}
	tmp[1] = 1
	a = 1
	b = 1
	i = iter(sorted(nset))
	try:
		n = i.next()
		while n == 1:
			n = i.next()
		for j in range(2, (10**6 + 2)):
			c = (b + (j-1)*a) % modulo
			while j == n:
				tmp[n] = c
				n = i.next()
			a = b
			b = c

	except StopIteration:
		pass
	ret = []
	for n in nset:
		ret.append(tmp[n])
	return ret