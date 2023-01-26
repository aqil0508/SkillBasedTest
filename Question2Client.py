import socket

#Set up the socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("192.168.255.128", 8080))
server_message = client_socket.recv(1024)
print(server_message.decode())

#User input
fahrenheit = float(input("Enter temperature in Fahrenheit: "))
fahrenheit_bytes = str(fahrenheit).encode()
client_socket.sendall(fahrenheit_bytes)

#Response from server
celsius_bytes = client_socket.recv(1024)
celsius = float(celsius_bytes.decode())
print("Temperature in Celsius: ", celsius)
client_socket.close()
