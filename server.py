import socket

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
        print from_client
        conn.send("Successful call to server\n")
        
    conn.close()
    print 'client disconnected'
    break
