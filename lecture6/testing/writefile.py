import csv
from cs50 import get_string


with open("phonebook.csv", "a") as file:
# could be: file = open('phonebook.csv', 'a')
    name = get_string('Name: ')
    number = get_string('Number: ')

    write = csv.writer(file)
    write.writerow([name, number]) # Writing the name and the number in a row
    
# then: file.close()