import random
import socket
import threading

#lists of quotes
quotes = ["“It hurt because it mattered.”", "“Don’t wait. The time will never be just right.”", "“Happiness is not by chance, but by choice.”", "“Either you run the day, or the day runs you.”","“Knowledge speaks, but wisdom listens.”","“No pressure, no diamonds.","“We will either find a way, or make one.”", "“I’m a slow walker, but I never walk back.”", "“The key to life is not accumulation. It’s contribution.”", "“We can’t help everyone, but everyone can help someone.” ","“Be not afraid of going slowly, be afraid only of standing still.”","“Rise above the storm and you will find the sunshine.”"]

#set up lists of quotes
def handle_client(client_socket):
    quote = random.choice(quotes)
    client_socket.send(quote.encode())
    client_socket.close()

#set up the server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("192.168.255.128", 8888))
server.listen(5)
print("Listening for incoming client...")

#set up response for client
while True:
    client, addr = server.accept()
    print("Received connection from:",addr)
    client_handler = threading.Thread(target=handle_client, args=(client,))
    client_handler.start()
