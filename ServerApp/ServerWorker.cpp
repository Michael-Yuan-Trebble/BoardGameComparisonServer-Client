#include "ServerWorker.h"
#include <qmessagebox.h>


void ServerWorker::startServer() 
{
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in service{};
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(54000);

    if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        qDebug() << "bind failed:" << WSAGetLastError();
        return;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        qDebug() << "listen failed:" << WSAGetLastError();
        return;
    }

    while (m_running) {
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(listenSocket, &readSet);

        timeval timeout{};
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        int sel = select(0, &readSet, nullptr, nullptr, &timeout);
        if (sel > 0 && FD_ISSET(listenSocket, &readSet)) {
            sockaddr_in clientAddr{};
            int addrSize = sizeof(clientAddr);
            SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrSize);
            if (clientSocket != INVALID_SOCKET) {
                char ipStr[INET_ADDRSTRLEN];
                InetNtopA(AF_INET, &clientAddr.sin_addr, ipStr, sizeof(ipStr));
                quint16 port = ntohs(clientAddr.sin_port);
                emit clientConnected(QString(ipStr), port);
                closesocket(clientSocket);
            }
        }
    }
    closesocket(listenSocket);
    m_listenSocket = INVALID_SOCKET;
}