#!/usr/bin/env python3
import socket
import os
import sys
import threading
HOST = '127.0.0.1' # Standard loopback interface address 
PORT = 8080 # Port to listen on



def send_dummy_response(conn, url):
    body='<html><body><h1>Requested:

def send_dummy_response(conn, url):
 body='<html><body><h1>Requested: %s</h1></body></html>' % url
 resp='HTTP/1.0 200 OK\r\n' + \
 'Connection: close\r\n' + \
 'Content-Type: text/html\r\n' + \
 'Content-Length: %d\r\n\r\n' % len(body) + body
 conn.sendall(resp.encode('utf-8'))
 time.sleep(1)
def parse_request(conn):
 request= ''
 while True:
 	request += conn.recv(1024).decode('utf-8')
 	if request.find('\r\n\r\n') >0:
 		break
 reqline, headers = request.split('\r\n', 1)
 method, url, version = reqline.split(' ', 3)
 return url
def serve_request(conn):
 #print('Connected by', addr)
 url=parse_request(conn)
 print(url)
 send_dummy_response(conn, url)
 conn.close()

# main
 s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 s.bind((HOST, PORT))
 s.listen()
 try:
 	while True:
 		# non-parallel version:
 		conn, addr = s.accept()
		serve_request(conn)
 finally:
	s.close()


