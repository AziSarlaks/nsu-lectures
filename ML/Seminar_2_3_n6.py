n = int(input())
r = []
s = 0
for i in range(n):
    r.append(list(map(int, input().split())))
for i in r:
    s = 0
    for j in i:
        if j > sum(i)/len(i):
            s+=1
    print(s)