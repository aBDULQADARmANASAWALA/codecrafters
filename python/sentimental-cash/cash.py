from cs50 import get_float


while True:
    change = get_float("Change: ") * 100
    if change > 0:
        break


coins = 0
for i in [25, 10, 5, 1]:
    coins += int(change / i)
    change %= i


print(int(coins))
