#include "ServerApp.h"

ServerApp::ServerApp(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("Server");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);


    MainLayout = new QVBoxLayout(centralWidget);
    ServerLabel = new QLabel("Server IP: " + QString(IPADDRESS), centralWidget);
    MainLayout->addWidget(ServerLabel);

    Table = new QTableWidget(centralWidget);
    Table->setColumnCount(2);
    Table->setHorizontalHeaderLabels({ "Client IP", "Port" });
    Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    Table->verticalHeader()->setVisible(false);
    Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Table->setSelectionMode(QAbstractItemView::NoSelection);

    MainLayout->addWidget(Table);

    startEndbtn = new QPushButton("Start", centralWidget);

    MainLayout->addWidget(startEndbtn);

    if (!setupSocket()) return;

    serverThread = new QThread(this);
    worker = new ServerWorker();
    worker->moveToThread(serverThread);

    connect(worker, &ServerWorker::clientConnected, this, &ServerApp::addClient);
    connect(worker, &ServerWorker::dataRecieved, this, &ServerApp::handleInput);
    connect(worker, &ServerWorker::clientDisconnected, this, &ServerApp::removeClient);

    connect(startEndbtn, &QPushButton::clicked, [this]() 
        {
        if (isStarted) 
        {
            QMetaObject::invokeMethod(worker, "stop", Qt::QueuedConnection);
            startEndbtn->setText("Start");
            isStarted = false;
        }
        else 
        {
            QMetaObject::invokeMethod(worker, "startServer", Qt::QueuedConnection);
            startEndbtn->setText("End");
            isStarted = true;
        }
    });

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

    WSACleanup();

    QMainWindow::closeEvent(event);
}

ServerApp::~ServerApp() 
{
    if (worker) worker->stop();
}

bool ServerApp::setupSocket()
{
    WSADATA wsaData;
    int wsaerr;

    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    { 
        QMessageBox::warning(
            this,
            "Warning",
            "Warning, WSA Startup failed",
            QMessageBox::Ok
        );
        return false;
    }
    return true;
}

void ServerApp::addClient(const QString& IP, quint16 port) 
{
    int row = Table->rowCount();
    Table->insertRow(row);
    Table->setItem(row, 0, new QTableWidgetItem(IP));
    Table->setItem(row, 1, new QTableWidgetItem(QString::number(port)));
}

void ServerApp::removeClient(const QString& IP, quint16 port) 
{
    for (int row = 0; row < Table->rowCount(); ++row)
    {
        QString tableIP = Table->item(row, 0)->text();
        QString tablePort = Table->item(row, 1)->text();

        if (tableIP == IP && tablePort == QString::number(port))
        {
            Table->removeRow(row);
            break;
        }
    }
}

void ServerApp::handleInput(QByteArray inData, SOCKET inSock)
{
    QString message = QString::fromUtf8(inData);
    if (message.startsWith("ROLL")) 
    {
        QStringList parts = message.split(' ');
        int sides = parts[1].toInt();
        int value = parts[2].toInt();
        rollDice(sides, value, inSock);
        
    }
}

void ServerApp::rollDice(int sides, int value, SOCKET inSock)
{
    int randomNum = QRandomGenerator::global()->bounded(1, sides + 1);
    QJsonObject reply{};
    reply["result"] = randomNum >= value;
    reply["serverResult"] = value;
    QByteArray sendClient = QJsonDocument(reply).toJson(QJsonDocument::Compact);
    send(inSock, sendClient.constData(), sendClient.size(), 0);
}