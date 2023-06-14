#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define PORT 4242
#define SERVER_ADDR "45.79.112.203"

int main()
{

    int socket_fd;
    struct sockaddr_in server_addr;

    char server_message[1024];
    char client_message[] = "This message is from client side";

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd < 0)
    {

        perror("socket()");
        exit(errno);
    }

    printf("Socket is successfully created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {

        perror("connect()");
        exit(errno);
    }

    printf("connected with server successfully\n");

    if (send(socket_fd, client_message, sizeof(client_message), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }

    if (recv(socket_fd, server_message, 1024, 0) < 0)
    {
        perror("recv");
        exit(errno);
    }

    printf("Server's message:- %s\n", server_message);

    close(socket_fd);
}