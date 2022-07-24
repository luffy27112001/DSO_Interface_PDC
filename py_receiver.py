from flask import Flask , request ,  render_template
from flask_socketio import SocketIO
from threading import Lock
async_mode = None
app = Flask(__name__)
app.config['SECRET_KEY'] =  'secret!'
socket_ = SocketIO(app , async_mode = async_mode)
thread = None
thread_lock = Lock()

@app.route('/')
def index():
    return render_template('simulation.html')

@app.route('/path' , methods = ['GET', 'POST'])
def view():
    if request.method == 'POST':
        array = request.json.get['data']
        print(array)