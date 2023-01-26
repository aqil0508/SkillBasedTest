import socket

#Set up connection
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("192.168.255.128", 8888))

#received response from server
received_quote = client.recv(4096).decode()
print("Received quote: ",received_quote)
