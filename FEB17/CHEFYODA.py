# Did you miss me ?
# I am back with Python in my arsenal bitches!

import math

t = int(input())
logfact = []
logfact.append(0)
for i in range(1, 1000001):
    logfact.append(logfact[i - 1] + math.log2(i))

while t > 0:
    n, m, p, k = map(int, input().split())
    winner1 = True
    winner2 = False
    ans = 0.0
    if n & 1 == 1 and m & 1 == 1:
        winner1 = False
    if n & 1 == 0 and m & 1 == 0:
        winner2 = True
    if winner1 == False and winner2 == False:
        if p == 0:
            ans = 1.0
        else:
            ans = 0.0
    elif winner1 == True and winner2 == True:
        ans = 1.0

    else:
        t1 = 1.0
        val = 1.0
        for i in range(1, k - p + 1):
            div = 1.0 * k - t1 + 1.0
            val = (val * t1 / div) + 1.0
            t1 += 1.0
        pw = math.log2(val) + logfact[k] - k - logfact[p] - logfact[k - p]
        ans = 2**pw
    print(float("{0:.9f}".format(ans)))
    t -= 1
