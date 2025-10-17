#include "ClientApp.h"

ClientApp::ClientApp(NetworkManager* inNet, QWidget* parent)
    : QMainWindow(parent)
{

    network = inNet;

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    MainLayout = new QVBoxLayout(centralWidget);

    Box = new QVBoxLayout(centralWidget);
    IPLayout = new QHBoxLayout(centralWidget);
    PortLayout = new QHBoxLayout(centralWidget);

    connectBtn = new QPushButton(centralWidget);
    connectBtn->setText("Connect to Server");

    connect(connectBtn, &QPushButton::clicked, this, &ClientApp::connectSocket);

    QLabel* IPLabel = new QLabel("Enter IP Address: ", centralWidget);

    IPAddressEdit = new QLineEdit(centralWidget);
    IPAddressEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    IPLayout->addWidget(IPLabel);
    IPLayout->addWidget(IPAddressEdit);

    QLabel* PortLabel = new QLabel("Enter Port: ", centralWidget);
    QIntValidator* intValid = new QIntValidator(PORTMIN, PORTMAX, this);

    PortEdit = new QLineEdit(centralWidget);
    PortEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    PortEdit->setValidator(intValid);

    PortLayout->addWidget(PortLabel);
    PortLayout->addWidget(PortEdit);

    MainLayout->setSpacing(1);

    Box->addWidget(connectBtn, 0, Qt::AlignHCenter);
    Box->addSpacing(50);
    Box->addLayout(IPLayout, 0);
    Box->addSpacing(50);
    Box->addLayout(PortLayout, 0);
    Box->addSpacing(200);


    MainLayout->addLayout(Box);
    resize(800, 800);
}

ClientApp::~ClientApp()
{
}

void ClientApp::connectSocket()
{
    /*
    IPAddress = IPAddressEdit->text();
    if (IPAddress.isEmpty()) return;
    IPAddress.trimmed();

    Port = PortEdit->text().toInt();
    if (Port == -1) return;
    */

    // For now for testing hardcoded, but can easily adapt to dynamic with:
    // network->connectToServer(IPAddress.toStdString().c_str(), Port)

    if (network->connectToServer(IPADDRESS, PORT))
    {
        emit connectedServer();
    }

}