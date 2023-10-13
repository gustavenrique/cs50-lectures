from cs50 import get_int

scores = []

for i in range(3):
    scores.append(get_int(f"Score {i+1}: "))

average = sum(scores) / len(scores) # Using useful functions
print(f'Average: {str(average)}') # The number has to be converted to string; Using formated print 