#!/usr/bin/env python
# -*- coding: utf-8 -*-
from cgi import parse_qs, escape

def hello_world(environ, start_response):
	parameters = parse_qs(environ.get('QUERY_STRING', ''))
	if 'subject' in parameters:
		subject = escape(parameters['subject'][0])
	else:
		subject = 'World'
	start_response('200 OK', [('Content-Type', 'text/plain')])
	return ['''Hello %(subject)s
	Hello %(subject)s!

''' % {'subject': subject}]

# if this file is called, start a webserver
if __name__ == '__main__':
	from wsgiref.simple_server import make_server
	srv = make_server('localhost', 8080, hello_world)
	srv.serve_forever()
