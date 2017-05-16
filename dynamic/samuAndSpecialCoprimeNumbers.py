"""
Samu had come up with new type of numbers, she named them Special Coprime numbers. Special Coprime numbers follow a property : A number N is said to be Special Coprime if sum of its digits as well as the sum of the squares of its digits are coprime to each other.

Now she started counting numbers that are Special Coprime. But soon she get bored and decided to write a program that can help do it. Now she want you to help her to find count of such numbers between L and R , where both L and R are included.
"""
def logNumber(digit, sum, sqrSum, g):
    #print(digit + '\t:GCD(' + str(sum) + ',' + str(sqrSum) + ') =\t' + str(g))
    pass

def gcd(l,r):
    mi = min(l,r)
    ma = max(l,r)
    if mi == 0:
        return ma
    return gcd(mi, ma - mi)

def samuAndSpecialCoprimeNumbersNaiveRecursive(digit, digitIdx, isLast, lastSum, lastSquareSum, digitSoFar = ''):

    if digitIdx >= len(digit):
        return 0

    ret = 0
    for i in range(0, 10):
        if isLast and i > int(digit[digitIdx]):
            break

        currentSum = lastSum + i
        currentSquareSum = lastSquareSum + i ** 2

        #if currentSum != 1 and currentSquareSum != 1:
        if digitIdx == len(digit) - 1:
            currentGcd = gcd(currentSum, currentSquareSum) 
            if currentGcd == 1:
                ret = ret + 1
            logNumber(digitSoFar + str(i), currentSum, currentSquareSum, currentGcd)
        
        if digitIdx == 0 and i == int(digit[digitIdx]):
            isLast = True

        ret = ret + samuAndSpecialCoprimeNumbersNaiveRecursive(digit, digitIdx + 1, isLast, currentSum, currentSquareSum, digitSoFar + str(i))

    return ret

def samuAndSpecialCoprimeNumbersNaive(L,R):
    strl = str(L - 1) # L is included
    lenl = len(strl) - 1
    spcl = samuAndSpecialCoprimeNumbersNaiveRecursive(strl, 0, lenl == 0, 0, 0)
    strr = str(R)
    lenr = len(strr) - 1
    spcr = samuAndSpecialCoprimeNumbersNaiveRecursive(strr, 0, lenr == 0, 0, 0)

    return spcr - spcl

print(samuAndSpecialCoprimeNumbersNaive(5,15))
print(samuAndSpecialCoprimeNumbersNaive(1,1000000000000000000))