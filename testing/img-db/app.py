from flask import Flask, request, render_template, Response
from werkzeug.utils import secure_filename

from cs50 import SQL

app = Flask(__name__)

db = SQL("sqlite:///img.db")

@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/upload', methods=['POST'])
def upload():
    pic = request.files['pic']
    
    if not pic:
        return 'No pic uploaded'
        
    filename = secure_filename(pic.filename)
    mime_type = pic.mimetype
    
    db.execute('INSERT INTO images (img, name, mime_type) VALUES(?, ?, ?)', pic.read(), filename, mime_type)
    
    return 'Image has been uploaded successfully!'
    

@app.route('/<int:id>')
def get_image(id):
    img = (db.execute('SELECT * FROM images WHERE id=?', id))[0]
    if not img:
        return 'no image with that id'
    
    return Response(img['img'], mimetype=img['mime_type'])
    
@app.route('/img/<int:id>')
def display_image(id):
    return render_template('image.html', id=id)
    
