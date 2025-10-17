#pragma once

#define IPADDRESS "127.0.0.1"
#define PORT 54000
#define PORTMAX 66535
#define PORTMIN 1

#include <iostream>
#include <WinSock2.h>
#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include <qobject.h>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qvalidator.h>
#include <qmessagebox.h>
#include "ui_ClientApp.h"
#include "NetworkManager.h"

class ClientApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientApp(NetworkManager* inNet, QWidget *parent = nullptr);
    ~ClientApp();

    SOCKET clientSocket;
    
    QString IPAddress;
    int Port = -1;

    QVBoxLayout* Box;
    QVBoxLayout* MainLayout;
    QHBoxLayout* IPLayout;
    QHBoxLayout* PortLayout;

    QLineEdit* IPAddressEdit;
    QLineEdit* PortEdit;

    QLabel* ConnectionDisplayLabel;
    QPushButton* connectBtn;

signals:
    void connectedServer();

private:

    NetworkManager* network;

    void connectSocket();
};

