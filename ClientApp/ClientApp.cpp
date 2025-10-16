#include "ClientApp.h"

ClientApp::ClientApp(NetworkManager* inNet, QWidget* parent)
    : QMainWindow(parent)
{

    network = inNet;

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    MainLayout = new QVBoxLayout(centralWidget);

    Layout = new QHBoxLayout(centralWidget);

    PortDisplay = new QLabel(QString("IP Address: %1").arg(IPADDRESS), centralWidget);

    Layout->addWidget(PortDisplay);

    connectBtn = new QPushButton(centralWidget);
    connectBtn->setText("Connect to Server");
    
    ConnectedLabel = new QLabel(centralWidget);

    Layout->addWidget(ConnectedLabel);

    connect(connectBtn, &QPushButton::clicked, this, &ClientApp::connectSocket);
    Layout->addWidget(connectBtn);
    MainLayout->addLayout(Layout);

    MainLayout->addWidget(PortDisplay);
}

ClientApp::~ClientApp()
{
}

void ClientApp::connectSocket()
{
    if (network->connectToServer(IPADDRESS, PORT))
    {
        emit connectedServer();
    }
    else
    {
        // TODO: Error
    }

}