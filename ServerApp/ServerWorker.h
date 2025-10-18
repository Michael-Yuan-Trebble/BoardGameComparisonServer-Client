#pragma once

#define IPADDRESS "127.0.0.1"
#define PORT 54000
#include <qthread.h>
#include <qdebug.h>
#include <WinSock2.h>
#include <qmessagebox.h>
#include <WS2tcpip.h>

class ServerWorker : public QObject 
{
	Q_OBJECT

public:

	explicit ServerWorker(QObject* parent = nullptr) : QObject(parent), m_running(true), m_listenSocket(INVALID_SOCKET) {}
	~ServerWorker();

	SOCKET listenSocket() const {
		return m_listenSocket;
	}

public slots:
	void startServer();

	void stop() { m_running = false; }
signals:
	void clientConnected(const QString &IP, quint16 port);

	void clientDisconnected(const QString& IP, quint16 port);

	void dataRecieved(QByteArray data, SOCKET client);

private:
	std::atomic<bool> m_running;
	SOCKET m_listenSocket;
	std::vector<SOCKET> clients;
};