#include "ClientApp.h"

ClientApp::ClientApp(QWidget* parent)
    : QMainWindow(parent)
{

    if (createClientSocket() != 0) qDebug() << "FAILED";

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    MainLayout = new QVBoxLayout(centralWidget);

    Layout = new QHBoxLayout(centralWidget);

    PortDisplay = new QLabel(QString("IP Address: %1").arg(IPADDRESS), centralWidget);

    Layout->addWidget(PortDisplay);

    QPushButton* ConnectSocket = new QPushButton(centralWidget);
    ConnectSocket->setText("Connect to Server");
    

    connect(ConnectSocket, &QPushButton::clicked, this, &ClientApp::connectSocket);
    Layout->addWidget(ConnectSocket);
    MainLayout->addLayout(Layout);

    MainLayout->addWidget(PortDisplay);
}

ClientApp::~ClientApp()
{
    if (clientSocket != INVALID_SOCKET) 
    {
        qDebug() << "Destructor Fired";
        closeAll(clientSocket);
    }
}

int ClientApp::createClientSocket() 
{
    WSAData wsaData;
    int wsaerr;

    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) 
    {
        qDebug() << "Client failed to detect WSA";
        return -1;
    }

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) 
    {
        qDebug() << "Client failed to open Socket";
        closeAll(clientSocket);
        return -1;
    }

    return 0;
}

void ClientApp::connectSocket()
{
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPtonA(AF_INET, IPADDRESS, &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(PORT);
    if (::connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        qDebug() << "Client failed to open port, WSA Error: " << WSAGetLastError();
        PortDisplay->setText(QString("ERROR"));
        closeAll(clientSocket);
        return;
    }
    PortDisplay->setText(QString("IP Address: %1").arg(PORT));
}

void ClientApp::closeAll(SOCKET inSock)
{
    closesocket(inSock);
    WSACleanup();
}