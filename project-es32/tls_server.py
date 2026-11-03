from http.server import BaseHTTPRequestHandler, HTTPServer
import ssl

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(content_length).decode()
        print("Received:", body)
        self.send_response(200)
        self.end_headers()

httpd = HTTPServer(("0.0.0.0", 8443), RequestHandler)

# Self-signed certificate generated with:
# openssl req -x509 -newkey rsa:2048 -keyout server.key -out server.crt -days 365 -nodes -subj "/CN=YOUR_SERVER_IP"
context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
context.load_cert_chain(certfile="certs/server.crt", keyfile="certs/server.key")
httpd.socket = context.wrap_socket(httpd.socket, server_side=True)

httpd.serve_forever()