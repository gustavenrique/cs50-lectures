import cs50
while True:
    height = cs50.get_int("Height: ")
    if height >= 1 and height <= 8:
        break
    
for line in range(1, height+1):
    for gap in range(height-line, 0, -1):
        print(' ', end='')
        
    for brick in range(1, line+1):
        print('#', end='')
        
    print()