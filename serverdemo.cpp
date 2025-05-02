#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *message = "Hello from server!";

    // Creating socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen for connections
    listen(server_fd, 3);

    // Accept a connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    read(new_socket, buffer, 1024);
    std::cout << "Message from client: " << buffer << std::endl;

    send(new_socket, message, strlen(message), 0);
    std::cout << "Hello message sent\n";

    close(new_socket);
    close(server_fd);
    return 0;
}
