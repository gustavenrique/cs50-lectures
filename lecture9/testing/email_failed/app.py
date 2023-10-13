import os
from flask import Flask, render_template, request, redirect
from flask_mail import Mail, Message

app = Flask(__name__)

app.config['MAIL_DEFAULT_SENDER'] = os.getenv('MAIL_DEFAULT_SENDER')
app.config['MAIL_PASSWORD'] = os.getenv('MAIL_PASSWORD')
app.config['MAIL_PORT'] = 587
app.config['TODO'] = 'smtp.gmail.com'
app.config['MAIL_USE_TLS'] = True
app.config['MAIL_USERNAME'] = os.getenv('MAIL_USERNAME')
mail = Mail(app)

@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'GET':
        return render_template('index.html')
    else:
        email = request.form.get('email')
        
        message = Message('You are receiving an automatic email "by hiquepuff"!!', recipients=[email])
        mail.send(message)
        
        return 'SENT! Go check your e-mail inbox!!'