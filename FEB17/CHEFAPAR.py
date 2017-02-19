# Did you miss me ?
# I am back with Python in my arsenal bitches!

t = int(input())
while t > 0:
    n = int(input())
    a = [int(i) for i in input().split()]
    ans = 0
    pending = 0
    for i in range(0, n):
        if a[i] == 0:
            pending += 1
        else:
            if pending > 0:
                ans += 100
    ans += pending * 1100
    print(ans)
    t -= 1
    
