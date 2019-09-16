import socket
import subprocess
import os
import sys 

# variables
port = 12345
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# listen on localhost
socket.bind(('127.0.0.1', port))
socket.listen(5)

# while listening
while True:
    conn, address = socket.accept()
    from_client = ''
    
    # while receiving
    while True:
        data = conn.recv(4096)
        if not data:
            break

        # append data to from_client
        from_client += data
        
        # pass the command from_client into os.popen
        output = os.popen(from_client).read()

        # print the command from_client
        print(from_client)

        # if touch is in from client, make output success since there is no output from touch command
        if 'touch' in from_client:
            output = 'Success!'

        # send the output back to the client
        conn.send(output)
        
        # reset from client to an empty string
        from_client = ''

    # close connection
    conn.close()
    print 'client disconnected'
    break
