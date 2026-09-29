import socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 9000))
payload = bytes([0x40, 0x00, 0x01]) + b'abcdef'
data = client_socket.send(payload)
print(bytes(client_socket.recv(1024)))
client_socket.close()
