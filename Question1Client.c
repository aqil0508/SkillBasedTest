#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
perror(msg);
exit(0);
} //Error function

int main()
{
    int socketFD, charsWritten, charsRead;
    struct sockaddr_in serverAddress;
    struct hostent* serverHostInfo;
    char buffer[256];
// Set up the server address struct
memset((char*)&serverAddress, '\0', sizeof(serverAddress));
serverAddress.sin_family = AF_INET;
serverAddress.sin_port = htons(8080);
serverAddress.sin_addr.s_addr = inet_addr("192.168.255.128");

// Set up the socket
socketFD = socket(AF_INET, SOCK_STREAM, 0);
if (socketFD < 0) error("CLIENT: ERROR opening socket");

// Connect to server
if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    error("CLIENT: ERROR connecting");

// Get random number from server
memset(buffer, '\0', sizeof(buffer));
charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
if (charsRead < 0) error("CLIENT: ERROR reading from socket");
printf("Random number from server: %s\n", buffer);

close(socketFD);
return 0;
}
