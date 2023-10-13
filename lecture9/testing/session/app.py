from flask import Flask, request, render_template, redirect, session
from flask_session import Session

app = Flask(__name__)
app.config['SESSION_PERMANENT']  = False
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)

@app.route('/')
def index():
    if not session.get('username'):
        return redirect('/login')
        
    return render_template('index.html')

@app.route('/login', methods=['POST', 'GET'])
def login():
    if request.method == 'POST':
        session['username'] = request.form.get('username')
        return redirect('/')
        
    return render_template('login.html')
     
@app.route('/logout') 
def logout():
    session['username'] = None
    
    return redirect('/')