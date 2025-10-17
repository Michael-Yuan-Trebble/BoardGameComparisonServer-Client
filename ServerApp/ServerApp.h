#pragma once

#include <QtWidgets/QMainWindow>
#include <qthread.h>
#include <WinSock2.h>
#include <QHBoxLayout>
#include <qlabel.h>
#include <WS2tcpip.h>
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

    SOCKET serverSocket;

    QHBoxLayout* MainLayout;
    QLabel* label;

private slots:
    void addClient(const QString& IP, quint16 port);

private:

    int setupSocket();

    void closeAll(SOCKET inSocket);

    QThread* serverThread;
    ServerWorker* worker;

protected:
    void closeEvent(QCloseEvent* event) override;
};

