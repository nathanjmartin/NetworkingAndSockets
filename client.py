import socket

# variables
port = 12345
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect(('', port))
socket.send("Response from client")

from_server = socket.recv(4096)
socket.close()

print from_server