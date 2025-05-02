#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from client!";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    send(sock, message, strlen(message), 0);
    std::cout << "Hello message sent\n";

    read(sock, buffer, 1024);
    std::cout << "Message from server: " << buffer << std::endl;

    close(sock);
    return 0;
}
