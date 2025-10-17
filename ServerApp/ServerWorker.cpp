#include "ServerWorker.h"
#include <qmessagebox.h>


void ServerWorker::startServer() 
{
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in service{};
    service.sin_family = AF_INET;
    InetPtonA(AF_INET, IPADDRESS, &service.sin_addr.s_addr);
    service.sin_port = htons(PORT);

    if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) 
    {
        QMessageBox::warning(
            nullptr,
            "Warning",
            "Warning, Server Bind Failed",
            QMessageBox::Ok
        );
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) 
    {
        QMessageBox::warning(
            nullptr,
            "Warning",
            "Warning, Server Listen Failed",
            QMessageBox::Ok
        );
        return;
    }

    while (m_running)
    {
        fd_set readSet{};
        FD_ZERO(&readSet);
        FD_SET(listenSocket, &readSet);

        for (SOCKET s : clients) FD_SET(s, &readSet);

        timeval timeout{};
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        int sel = select(0, &readSet, nullptr, nullptr, &timeout);
        if (sel == SOCKET_ERROR) break;

        if (FD_ISSET(listenSocket, &readSet))
        {
            sockaddr_in clientAddr{};
            int addrSize = sizeof(clientAddr);
            SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrSize);
            if (clientSocket != INVALID_SOCKET)
            {
                char ipStr[INET_ADDRSTRLEN];
                InetNtopA(AF_INET, &clientAddr.sin_addr, ipStr, sizeof(ipStr));
                quint16 port = ntohs(clientAddr.sin_port);

                emit clientConnected(QString(ipStr), port);

                clients.push_back(clientSocket);
            }
        }

        for (auto it = clients.begin(); it != clients.end(); )
        {
            SOCKET clientSocket = *it;
            if (FD_ISSET(clientSocket, &readSet))
            {
                char buffer[512];
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0)
                {
                    sockaddr_in addr{};
                    int len = sizeof(addr);
                    getpeername(clientSocket, (sockaddr*)&addr, &len);

                    char ipStr[INET_ADDRSTRLEN];
                    InetNtopA(AF_INET, &addr.sin_addr, ipStr, sizeof(ipStr));
                    quint16 port = ntohs(addr.sin_port);

                    emit clientDisconnected(QString(ipStr), port);

                    closesocket(clientSocket);
                    it = clients.erase(it);
                    continue;
                }
                else
                {
                    
                }
            }
            ++it;
        }
    }
    closesocket(listenSocket);
    m_listenSocket = INVALID_SOCKET;
}