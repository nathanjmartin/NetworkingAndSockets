import socket
import subprocess
import os

# variables
port = 12345
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

socket.bind(('127.0.0.1', port))
socket.listen(5)

while True:
    conn, address = socket.accept()
    from_client = ''
    
    while True:
        data = conn.recv(4096)
        if not data:
            break
        from_client += data
        
        # take from_client and pass into subprocess to execute a command
        # and return that output
        # how can i replace 'ls' with 'from_client' without getting null characters error
        output = os.popen(from_client).read()
        print(from_client)
        conn.send(output)
        output = 'Success!'
        from_client = ''
        
    conn.close()
    print 'client disconnected'
    break
