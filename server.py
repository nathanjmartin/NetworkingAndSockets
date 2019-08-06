import socket
import subprocess


# variables
port = 12345
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

socket.bind(('', port))
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
        output = subprocess.Popen(['ls'], stdout=subprocess.PIPE)
        out, err = output.communicate()
        print(from_client)
        conn.send(out)
        
    conn.close()
    print 'client disconnected'
    break
