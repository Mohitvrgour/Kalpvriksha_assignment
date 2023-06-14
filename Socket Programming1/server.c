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

    int sfd, client_size, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t new_addr;
    char client_message[1024];
    char server_message[] = "This is server's message";

    // memset(&server_message, 0 , sizeof(server_message));
    // memset(&client_message,0 , sizeof(client_message));

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("socket()");
        exit(errno);
    }
    printf("Socket is successfully created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {

        perror("bind()");
        exit(errno);
    }

    printf("bind success\n");

    if (listen(sfd, 1) < 0)
    {
        perror("listen()");
        exit(errno);
    }

    printf("listening...\n");

    client_fd = accept(sfd, (struct sockaddr *)&server_addr, &new_addr);

    if (client_fd < 0)
    {
        perror("accept()");
        exit(errno);
    }

    if (recv(client_fd, &client_message, 1024, 0) < 0)
    {
        perror("recv");
        exit(errno);
    }

    printf("Message from client's side:- %s\n", client_message);

    if (send(client_fd, server_message, sizeof(server_message), 0) < 0)
    {

        perror("send()");
        exit(errno);
    }

    close(client_fd);
    close(sfd);
}