from cs50 import get_string

people = {
    'Babu': '+55 11 9003-8922',
    'Bigu': '+43 12 3748-3920'
}

name = get_string("Name: ")

if name in people:
    print(f'Number: {people[name]}')