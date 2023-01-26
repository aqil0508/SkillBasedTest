#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
perror(msg);
exit(1);
} // Error function

int main()
{
    int listenSocketFD, establishedConnectionFD, charsRead;
    socklen_t sizeOfClientInfo;
    char buffer[256];
    srand(time(0));
    struct sockaddr_in serverAddress, clientAddress;

    // Set up the address struct for this process (the server)
    memset((char *)&serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Set up the socket
    listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocketFD < 0) error("ERROR opening socket");

    // Enable the socket to listening
    if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        error("ERROR on binding");
    listen(listenSocketFD, 5);

    // Accept a connection
    sizeOfClientInfo = sizeof(clientAddress);
    establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo);
    if (establishedConnectionFD < 0) error("ERROR on accept");

    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), str, INET_ADDRSTRLEN);
    printf("Server is now connected to a client with IP address: %s\n", str);

    // Generate random number between 100 and 999
    int randomNumber = rand() % 900 + 100;
    sprintf(buffer, "%d", randomNumber);

    // Send the random number to the client
    charsRead = send(establishedConnectionFD, buffer, strlen(buffer), 0);
    if (charsRead < 0) error("ERROR writing to socket");

    close(establishedConnectionFD);
    close(listenSocketFD);
    return 0;
}
