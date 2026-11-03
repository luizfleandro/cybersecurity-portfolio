from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(content_length).decode()
        print("Received:", body)
        self.send_response(200)
        self.end_headers()

HTTPServer(("0.0.0.0", 8080), RequestHandler).serve_forever()