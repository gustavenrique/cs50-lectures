import cs50

cents = 0
coins = 0
qrt = 25
dm = 10
nc = 5
pn = 1

while True:
    change = cs50.get_float("Change owed: ") * 100
    
    if change >= 1:
        break
    
while cents + qrt <= change:
    coins = coins + 1
    cents = cents + qrt
    
while cents + dm <= change:
    coins = coins + 1
    cents = cents + dm
    
while cents + nc <= change:
    coins = coins + 1
    cents = cents + nc
    
while cents + pn <= change:
    coins = coins + 1
    cents = cents + pn
    
print(coins)