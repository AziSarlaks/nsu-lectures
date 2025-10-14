n = int(input())
c = 0
cn = 0
nick = []
for i in range(n):
    x = input()
    if x.split(': ')[1] == "Correct" and x not in nick:
        c+=1
        cn+=1
        nick.append(x)
    elif x.split(': ')[1] == "Correct" and x in nick:
        cn+=1
    elif x not in nick:
        nick.append(x)
print(cn)
p = round(cn / n * 100)
if c != 0:
    print(f"Верно решили {c} учащихся")
    print(f"Из всех попыток {p}% верных")
else:
    print("Вы можете стать первым, кто решит эту задачу")