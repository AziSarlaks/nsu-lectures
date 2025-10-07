n = int(input())
c = 0
nick = []
for i in range(n):
    x = input().split(': ')
    if x[1] == "Correct" and x[0] not in nick:
        c+=1
        nick.append(x[0])
    elif x[0] not in nick:
        nick.append(x[0])
p = c / len(nick) * 100
if c != 0:
    print(f"Верно решили {c} учащихся")
    print(f"Из всех попыток {p}% верных")
else:
    print("Вы можете стать первым, кто решит эту задачу")