import sys
import csv

def main():
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py data.csv sequence.txt')
        
    elif '.csv' in sys.argv[1] and '.txt' in sys.argv[2]:
        # Getting the people data
        people = []
        with open(sys.argv[1]) as csvfile:
            csvreader = csv.DictReader(csvfile)
            
            for person in csvreader:
                people.append(person)
                
        # Opening the DNA text file and getting its content
        with open(sys.argv[2]) as dna_txt:
            dna_sequence = dna_txt.read()
            
        # Getting the STRs
        dna_strs = {}
        for STR in people[0].keys():
            if STR != 'name':
                dna_strs[STR] = 0
        
        count_strs(dna_strs, dna_sequence)
        
        # In a loop of people
        for person in people:
            # If the person has the DNA, print it
            if dna_test(person, dna_strs) == True:
                print(person['name'])
                sys.exit(0)
        print('No match')
    else:
        sys.exit('Usage: python dna.py data.csv sequence.txt')
        
        
def count_strs(dna_strs, dna_sequence):
    current = 0
    maximum = 0
    last_i = 0
    
    # In a loop of the STR's we've got...
    for STR in dna_strs:
        # Look for the STR, and if we come across one...
        for i in range(len(dna_sequence)):
            if dna_sequence[i:i+len(STR)] == STR:
                # Count how many times it repeats consecutively
                current = current + 1
                last_i = i
            elif i == last_i + len(STR):
                if current > maximum:
                    maximum = current
                current = 0
                
        dna_strs[STR] = maximum
        maximum = 0
                
        
def dna_test(person, dna_strs):
    for STR in dna_strs:
        if int(person[STR]) !=  int(dna_strs[STR]):
            return False
    return True
    
    
if __name__ == '__main__':
    main()