from flask import Flask, render_template, request
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

@app.route('/')
def index():
    return render_template('index.html')

# Recebe /joystick?x=<int>&y=<int>
@app.route('/joystick', methods=['GET'])
def joystick():
    x = request.args.get('x', type=int, default=0)
    y = request.args.get('y', type=int, default=0)
    print(f"Joystick X={x}% Y={y}%")
    socketio.emit('joystick', {'x': x, 'y': y})
    return 'OK', 200

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)
