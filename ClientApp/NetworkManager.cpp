#include "NetworkManager.h"

NetworkManager::NetworkManager(QObject* parent) : QObject(parent) 
{

}

NetworkManager::~NetworkManager() 
{
	closeConnection();
	WSACleanup();
}

bool NetworkManager::init() 
{
    WSAData wsaData;
    int wsaerr;

    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        emit errorOccured("Failed to initialize WSA");
        return false;
    }

    return true;
}

bool NetworkManager::connectToServer(const char* ip, int port) 
{
    clientSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        emit errorOccured("Failed to create Socket");
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    InetPtonA(AF_INET, ip, &serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons(port);
    if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        emit errorOccured(QString("Connect failed, error: %1").arg(WSAGetLastError()));
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
        return false;
    }

    connectedFlag = true;
    emit connected();

    running = true;
    std::thread([this]() {recieveLoop(); }).detach();

    return true;
}

void NetworkManager::recieveLoop()
{
    char buffer[512];
    while (running && connectedFlag)
    {
        int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytes > 0)
        {
            emit messageRecieved(QByteArray(buffer, bytes));
        }
        else if (bytes == 0)
        {
            emit disconnected();
            break;
        }
        else 
        {
            emit errorOccured(QString("recv() failed: %1").arg(WSAGetLastError()));
            break;
        }
    }
    connectedFlag = false;
}

bool NetworkManager::sendData(const char* data, int size) 
{
    if (send(clientSocket, data, size, 0) == SOCKET_ERROR)
    {
        emit errorOccured(QString("send() failed: %1").arg(WSAGetLastError()));
        return false;
    }
    return true;
}

void NetworkManager::closeConnection() 
{
    running = false;
    if (clientSocket==INVALID_SOCKET)
    {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
    connectedFlag = false;
}