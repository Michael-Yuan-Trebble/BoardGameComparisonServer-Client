#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <QObject>
#include <QDebug>
#include <thread>

class NetworkManager : public QObject {
	Q_OBJECT

public:
	explicit NetworkManager(QObject* parent = nullptr);
	~NetworkManager();

	bool init();
	bool connectToServer(const char* ip, int port);
	bool sendData(const char* data, int size);
	void closeConnection();

	SOCKET socket() const { return clientSocket; }

signals:
	void connected();
	void disconnected();
	void messageRecieved(QByteArray data);
	void errorOccured(QString message);

private:
	SOCKET clientSocket = INVALID_SOCKET;
	bool connectedFlag = false;
	bool running = false;

	void recieveLoop();
};