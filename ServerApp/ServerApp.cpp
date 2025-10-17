#include "ServerApp.h"

ServerApp::ServerApp(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    MainLayout = new QHBoxLayout(centralWidget);
    label = new QLabel("Server", centralWidget);
    MainLayout->addWidget(label);

    if (setupSocket() != 0) 
    {
        qDebug() << "ERROR";
    }

    serverThread = new QThread(this);
    worker = new ServerWorker();
    worker->moveToThread(serverThread);

    connect(serverThread, &QThread::started, worker, &ServerWorker::startServer);
    connect(worker, &ServerWorker::clientConnected, this, &ServerApp::addClient);

    serverThread->start();

    resize(800, 800);
}

void ServerApp::closeEvent(QCloseEvent* event) 
{
    if (worker && serverThread) 
    {
        worker->stop();
        closesocket(worker->listenSocket()); 
        serverThread->quit(); 
        serverThread->wait(); 
        worker->deleteLater();
        serverThread->deleteLater();
    }

    QMainWindow::closeEvent(event);
}

ServerApp::~ServerApp()
{
    if (serverSocket != INVALID_SOCKET)
    {
        closeAll(serverSocket);
    }
}

int ServerApp::setupSocket()
{
    WSADATA wsaData;
    int wsaerr;

    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    { 
        qDebug() << "Server WSA start up failed"; 
        return -1; 
    }

    return 0;
}

void ServerApp::addClient(const QString& IP, quint16 port) 
{
    label->setText(QString::number(port));
}

void ServerApp::closeAll(SOCKET inSocket) 
{
    closesocket(inSocket);
    WSACleanup();
}