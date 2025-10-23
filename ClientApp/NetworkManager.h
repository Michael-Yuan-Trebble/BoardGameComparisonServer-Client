#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <QObject>
#include <qjsondocument.h>
#include <QDebug>
#include <qjsonobject.h>
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

	bool running = false;

	SOCKET socket() const { return clientSocket; }

signals:
	void connected();
	void disconnected();
	void messageRecieved(QJsonObject reply);
	void errorOccured(const QString& message);

private:
	SOCKET clientSocket = INVALID_SOCKET;
	bool connectedFlag = false;

	void recieveLoop();
};