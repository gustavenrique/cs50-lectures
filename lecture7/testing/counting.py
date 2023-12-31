import csv

titles = {}

with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        title = row["title"].strip().upper()
        if title not in titles:
            titles[title] = 0
        titles[title] += 1

# Sorting by the values in descending order
for title in sorted(titles, key=lambda title: titles[title], reverse=True): 
    print(title, titles[title])