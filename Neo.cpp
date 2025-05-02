#include "Neo.h"

Neo::Neo()
{
    readRemnant = "";
    sockfd = newSocketfd = 0;
    socketType = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket == 0)
    {
        perror("Socket initialization failed");
        exit(EXIT_FAILURE);
    }
}

void Neo::initServer(int PORT)
{
    socketType = 1;
    myServerAddr.sin_family = AF_INET;
    myServerAddr.sin_addr.s_addr = INADDR_ANY;
    myServerAddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&myServerAddr, sizeof(myServerAddr));
    listen(sockfd, 1);
}

void Neo::initClient(std::string ipAddr, int PORT)
{
    socketType = 2;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, ipAddr.c_str(), &serverAddr.sin_addr);
}

void Neo::acceptConnection()
{
    int addrlen = sizeof(clientAddr);
    newSocketfd = accept(sockfd, (struct sockaddr *)&clientAddr, (socklen_t *)&addrlen);
}

bool Neo::clientConnect()
{
    int status = connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (status != 0)
        return false;
    return true;
}

std::pair<std::shared_ptr<uint8_t>, int> Neo::readData()
{
    int readSocket = 0;
    switch (socketType)
    {
    case 1:
        readSocket = newSocketfd;
        break;
    case 2:
        readSocket = sockfd;
        break;
    default:
        std::cout << "socket not initialized!\n";
        return {nullptr, -1};
    }

    std::string data = readRemnant;
    uint8_t buffer[1024];
    while (true)
    {
        size_t bytesRead = read(readSocket, buffer, 1024 - 1);
        buffer[bytesRead] = '\0';
        data.append((char *)buffer, bytesRead);
        size_t pos = data.find("EndOfMessage");
        if (pos != std::string::npos)
            break;
    }

    size_t pos = data.find("EndOfMessage");
    data = data.substr(0, pos);
    readRemnant = data.substr(pos);

    char *dataPointer = new char[data.size()];
    std::memcpy(dataPointer, data.c_str(), data.size());
    std::shared_ptr<uint8_t> finalData((uint8_t *)dataPointer);
    return {finalData, data.size()};
}

int Neo::writeData(std::shared_ptr<uint8_t> data, int length)
{
    std::string messageTerminator = "EndOfMessage";
    int totalLength = length + messageTerminator.size();
    std::shared_ptr<uint8_t> terminatedData(new uint8_t[totalLength], std::default_delete<uint8_t[]>());
    std::memcpy(terminatedData.get(), data.get(), length);
    std::memcpy(terminatedData.get() + length, messageTerminator.c_str(), messageTerminator.size());
    switch (socketType)
    {
    case 1:
        send(newSocketfd, terminatedData.get(), totalLength, 0);
        break;
    case 2:
        send(sockfd, terminatedData.get(), totalLength, 0);
        break;
    default:
        std::cout << "socket not initialized!\n";
        return -1;
    }
    return totalLength;
}
