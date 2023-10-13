import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session['user_id']
    
    companys = db.execute('SELECT symbol, name, SUM(shares) AS currentShares FROM transactions WHERE user_id=? GROUP BY symbol;', user_id)
    cash = db.execute('SELECT cash FROM users WHERE id = ?', user_id)[0]['cash']
    
    total = cash
    
    for company in companys:
        total += lookup(company['symbol'])['price'] * company['currentShares']
    
    return render_template('index.html', cash=cash, companys=companys, total=total, usd=usd, lookup=lookup)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'GET':
        return render_template('buy.html')
    else:
        '''Getting the symbol'''
        symbol = request.form.get('symbol').upper()
        if not symbol:
            return apology('missing symbol')
        
        '''Getting the company informations'''
        company = lookup(symbol)
        if not company:
            return apology('wrong symbol')
        
        name = company['name']
            
        '''Getting the user informations'''
        user_id = session['user_id']
        cash = db.execute('SELECT cash FROM users WHERE id = ?;', user_id)[0]['cash']
        
        """Doing the transactions"""
        price = float(company['price'])
        shares = int(request.form.get('shares'))
        if not shares:
            return apology('missing shares')
        
        if cash >= (price*shares):
            db.execute('INSERT INTO transactions (user_id, symbol, name, price, shares, type) VALUES(?, ?, ?, ?, ?, ?);',
                       user_id, symbol, name, price, shares, 'buy')
            new_cash = cash - (price*shares)
            db.execute('UPDATE users SET cash = ? WHERE id = ?;', new_cash, user_id)
        else:
            return apology('not enough cash')
        
        return redirect('/')
        


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session['user_id']
    
    transactions = db.execute('SELECT symbol, name, shares, price, time FROM transactions WHERE user_id=?;', user_id)

    return render_template('history.html', transactions=transactions, usd=usd)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == 'GET':
        return render_template('quote.html')
    else:
        symbol = request.form.get('symbol')
        
        if not symbol:
            return apology('missing symbol')
        
        company = lookup(symbol)
        if not company:
            return apology('wrong symbol')
            
        return render_template('quoted.html', name=company['name'], symbol=company['symbol'], price=company['price'], usd=usd)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'GET':
        return render_template('register.html')
    else:
        # Ensure username was submitted
        if not request.form.get('username'):
            return apology('must provide username')

        # Check if username is already taken
        userList = db.execute('SELECT * FROM users;')

        if len(userList) > 0:
            for person in userList:
                if person['username'] == request.form.get('username'):
                    return apology('username already taken')

        # Ensure password was submitted
        if not request.form.get('password'):
            return apology('must provide password')

        # Ensure confirmation was submitted
        if not request.form.get('confirmation'):
            return apology('must provide confirmation')

        # Check if passwords match
        if request.form.get('password') != request.form.get('confirmation'):
            return apology("password don't match")

        # Generating a password hash and inserting the user into the database
        hash_pass = generate_password_hash(request.form.get('password'))

        db.execute('INSERT INTO users (username, hash) VALUES(?, ?)', request.form.get('username'), hash_pass)
        # Redirect user to login page
        return redirect('/login')

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session['user_id']
    
    if request.method == 'GET':
        companys = db.execute('SELECT symbol, SUM(shares) AS currentShares FROM transactions WHERE user_id = ? GROUP BY symbol;', user_id)
        return render_template('sell.html', companys=companys)
    else:
        symbol = request.form.get('symbol').upper()
        if not symbol:
            return apology('missing symbol')
        
        company = lookup(symbol)
        if not company:
            return apology('wrong symbol')
            
        shares = int(request.form.get('shares'))
        if not shares:
            return apology('missing amount of shares')
            
        userShares = db.execute('SELECT SUM(shares) AS currentShares FROM transactions WHERE user_id = ? AND symbol = ?;',
        user_id, symbol)[0]['currentShares']
        
        cash = db.execute('SELECT cash FROM users WHERE id = ?;', user_id)[0]['cash']
        
        if userShares < shares:
            return apology('not enough shares')
        else:
            db.execute('INSERT INTO transactions (user_id, symbol, name, price, shares, type) VALUES(?, ?, ?, ?, ?, ?);', 
            user_id, symbol, company['name'], company['price'], (shares-shares*2), 'sell')
            
            newCash = cash + company['price']*shares
            db.execute('UPDATE users SET cash = ? WHERE id = ?;', newCash, user_id)
        
        return redirect('/')

@app.route('/settings', methods=['POST', 'GET'])
@login_required
def config():
    """ Changing the user pass """
    
    user_id = session['user_id']
    
    if request.method == 'GET':
        return render_template('settings.html')
    else:
        currentPass = request.form.get('current-pass')
        if not currentPass:
            return apology('missing current pass')
        
        newPass = request.form.get('new-pass')
        if not newPass:
            return apology('missing new pass')
            
        confirmation = request.form.get('confirmation')
        if not confirmation:
            return apology('missing confirmation')

        """ Checking if the current pass is right"""
        userPass = db.execute('SELECT hash FROM users WHERE id = ?;', user_id)[0]['hash']
        
        if not check_password_hash(userPass, currentPass):
            return apology('wrong current pass', 403)
        
        """ Checking if the confirmation match """
        if confirmation != newPass:
            return apology("confirmation didn't match")
        else:
            newPass = generate_password_hash(newPass)
            
            db.execute('UPDATE users SET hash = ? WHERE id=?;', newPass, user_id)
            
            return redirect('/')
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
