
import math

def int2bin(n):
    """returns the binary of integer n, using count number of digits"""
    if n == 0:
        return str(n)
    return "".join([str((n >> y) & 1)
                    for y in range(int(math.log(n, 2)), -1, -1)])



def target_patterns():
    for i in range(512):
        binary = int2bin(i)
        if binary.count('1') >= 4:
            yield binary


print 'Number of subsets: ', len(list(target_patterns()))


def factorial(n):
    ret = 1
    for i in range(2, n+1):
        ret *= i
    return ret



def calculate_order():
    return sum(factorial(pattern.count('1')) for pattern in target_patterns())


print 'Number of combinations: ', calculate_order()
