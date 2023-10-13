from cs50 import get_int

# Creating the main function
def main(): 
    s = get_int("How many meows? ")
    meow(s)

# Creating the meow function
def meow(n):
    for i in range(n):
        print('meow')
        
# Calling the main function
main()