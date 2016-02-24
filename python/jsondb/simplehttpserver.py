#!/usr/bin/python
    
import SimpleHTTPServer
import BaseHTTPServer

PORT = 8003

# open json file

class Handler(BaseHTTPServer.BaseHTTPRequestHandler):
	def do_GET( self ):
		
		# check if location is available
			# no, send 404
			# yes stream data		
		
		self.wfile.write(self.path + "\n\n");
		self.send_response(200)
		self.send_header( 'Content-type', 'text/html' )
		self.end_headers()
		self.wfile.write( open('simplehttpserver.py').read() )
	
if __name__ == '__main__':
	httpd = BaseHTTPServer.HTTPServer(("", PORT), Handler)
	print "Serving at port", PORT
	httpd.serve_forever()
