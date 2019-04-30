from flask import Flask, jsonify, request, render_template
import time
from subprocess import Popen, PIPE
app = Flask(__name__)


def serve_homepage():
    f=open("html/main.html", "r")
    return f.read()


def process_post():
    code = request.form['code']

    file_name = "temp/" +str(time.time()) + ".txt"

    file1 = open(file_name,"w")
    file1.write(code)
    file1.close()

    process = Popen(["build/QSim", file_name], stdout=PIPE)
    (output, err) = process.communicate()
    exit_code = process.wait()

    return output

@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        return process_post()
    else:
        return serve_homepage()


if __name__ == '__main__':
    app.run()
