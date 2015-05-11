from math import *

# Open a file in write mode
fo = open("test.txt", "rw+")

def fx(x):
    return cos(2*x*2.0*pi) + cos(10.0*x*2.0*pi) + 2
    #return 0
def fy(x):
    return 0
def fz(x):
    return 0

def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

for x in my_range(0,10, 0.01):
    fo.write(str(fx(x)) + '\t' + str(fy(x)) + '\t' + str(fz(x)))
    fo.write('\n');
    
fo.close()