#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include <cstring>
#include <vector>
class Neo
{
private:
    int sockfd;
    struct sockaddr_in serverAddr;   // for client mode
    struct sockaddr_in myServerAddr; // for server mode
    struct sockaddr_in clientAddr;
    int newSocketfd;
    int socketType;
    std::string readRemnant;

public:
    Neo();
    void initServer(int PORT);
    void initClient(std::string ipAddr, int PORT);
    void acceptConnection();
    bool clientConnect();
    std::pair<std::shared_ptr<uint8_t>, int> readData();
    int writeData(std::shared_ptr<uint8_t> data, int length);
};