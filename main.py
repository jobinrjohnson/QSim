from flask import Flask, jsonify, request, render_template, make_response
import time
from subprocess import Popen, PIPE
import os
app = Flask(__name__, static_folder="web", template_folder="web")


def serve_homepage():
    return render_template("main.html")


def process_post():
    code = request.form['code']

    file_name = "temp/" + str(time.time()) + ".txt"

    file1 = open(file_name, "w")
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


@app.route('/sw.js')
def sw_js():
    headers = {'Content-Type': 'application/javascript'}
    return make_response(render_template('sw.js'),200,headers)
    


if __name__ == '__main__':
    app.run()
