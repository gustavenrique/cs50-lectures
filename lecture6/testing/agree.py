import cs50

s = cs50.get_string("Do you agree? ")

if s.lower() in ["y", "yes"]:
    print("Agreed.")
elif s.lower() in ['n', 'no']:
    print("Not agreed.")
else:
    print("Huh?")