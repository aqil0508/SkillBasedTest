import socket

#Fehrenheit to celcius formula
def fahrenheit_to_celsius(fahrenheit):
    return (fahrenheit - 32) * 5/9

#Set up the server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("192.168.255.128", 8080))
server_socket.listen(1)
print("Listening for incoming client...")

#Set up for client connection
while True:
    client_socket, client_address = server_socket.accept()
    print("Server is now connected to: ", client_address)
    client_socket.sendall(b"Connected to the temperature conversion server")
    fahrenheit_bytes = client_socket.recv(1024)
    fahrenheit = float(fahrenheit_bytes.decode())
    celsius = fahrenheit_to_celsius(fahrenheit)
    celsius_bytes = str(celsius).encode()
    client_socket.sendall(celsius_bytes)
    client_socket.close()
