from cs50 import SQL

open('bbb.db', 'w').close()
db = SQL('sqlite:///bbb.db')

db.execute('CREATE TABLE bbb(id INTEGER, guest_name TEXT, edition TEXT, PRIMARY KEY(id));')

name = input("Guest name: ").strip().upper()
edition = input('Edition: ').strip().upper()

db.execute('INSERT INTO bbb (guest_name, edition) VALUES(?, ?)', name, edition)
