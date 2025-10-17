#pragma once

#define IPADDRESS "127.0.0.1"
#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include <WinSock2.h>
#include <QHBoxLayout>
#include <qlabel.h>
#include <WS2tcpip.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include <qheaderview.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include "ui_ServerApp.h"
#include "ServerWorker.h"

class ServerApp : public QMainWindow
{
    Q_OBJECT

public:
    ServerApp(QWidget *parent = nullptr);
    ~ServerApp();

private slots:
    void addClient(const QString& IP, quint16 port);
    void removeClient(const QString& IP, quint16 port);

private:
    bool setupSocket();
    void closeAll(SOCKET inSocket);

    SOCKET serverSocket;

    QVBoxLayout* MainLayout;
    QLabel* ServerLabel;
    QTableWidget* Table;
    QThread* serverThread;

    ServerWorker* worker;

protected:
    void closeEvent(QCloseEvent* event) override;
};

