# Did you miss me ?
# I am back with Python in my arsenal bitches!

t = int(input())
while t > 0:
    o1, o2 = map(int, input().split())
    n = o1 * o2
    a = [int(i) for i in input().split()]
    sum = []
    sum.append(a[0])
    for i in range(1, n):
        sum.append(sum[i - 1] + a[i])
    ok = False
    for i in range(0, o2):
        one = 0
        zero = 0
        for k in range(0, o1):
            cnt = 0
            j = k * o2 + i
            if j + o2 - 1 >= n:
                jj = (j + o2 - 1) % n
                if j == 0:
                    cnt = sum[n - 1] + sum[jj]
                else:
                    cnt = sum[n - 1] - sum[j - 1] + sum[jj]
            else:
                jj = (j + o2 - 1) % n
                if j == 0:
                    cnt = sum[jj]
                else:
                    cnt = sum[jj] - sum[j - 1]
            if cnt > o2 - cnt:
                one += 1
            else:
                zero += 1
        if one > zero:
            ok = True
            break
    if ok == True:
        print(1)
    else:
        print(0)
    t -= 1
