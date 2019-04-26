from subprocess import Popen, PIPE
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import SocketServer
import cgi
import time


class S(BaseHTTPRequestHandler):

    def do_GET(self):

        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        f=open("html/main.html", "r")
        self.wfile.write(f.read())

    def do_POST(self):

        form = cgi.FieldStorage(
            fp=self.rfile,
            headers=self.headers,
            environ={'REQUEST_METHOD': 'POST'}
        )

        code = form.getvalue("code")

        file_name = "temp/" +str(time.time()) + ".txt"

        file1 = open(file_name,"w")
        file1.write(code) 
        file1.close() 

        process = Popen(["build/QSim", file_name], stdout=PIPE)
        (output, err) = process.communicate()
        exit_code = process.wait()

        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(output)


def startServer(port=8090):
    server_address = ('', port)
    httpd = HTTPServer(server_address, S)
    print('Starting server...')
    httpd.serve_forever()


if __name__ == "__main__":
    startServer()
