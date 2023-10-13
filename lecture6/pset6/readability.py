import cs50

def main():
    txt = cs50.get_string("Text: ")
    length = len(txt)
    
    # Counting the letters
    letters = 0
    for i in range(length):
        if txt[i].isalpha():
            letters = letters + 1
    
    # Counting the words
    words = 1
    for i in range(length):
        if txt[i].isspace():
            words = words + 1
        
    # Counting the sentences
    sent = 0
    for i in range(length):
        if txt[i] in ['.', '!', '?']:
            sent = sent + 1
    
    # Calculating the indices and grade
    L = (letters * 100) / float(words)
    S = (sent * 100) / float(words)
    grade = (0.0588 * L) - (0.296 * S) - 15.8
    
    # Displaying the result
    if grade > 16:
        print('Grade 16+')
    elif grade < 1:
        print('Before Grade 1')
    else:
        print(f'Grade {round(grade)}')
    
main()