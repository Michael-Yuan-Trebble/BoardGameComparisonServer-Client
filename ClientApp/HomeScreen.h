#pragma once

#include <QtWidgets/qmainwindow.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcombobox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qcheckbox.h>
#include <qjsondocument.h>
#include <qmessagebox.h>
#include <qrandom.h>
#include <random>
#include <ctime>

class NetworkManager;
class FileManager;

class HomeScreen : public QMainWindow 
{
	Q_OBJECT
public:
	HomeScreen(NetworkManager* inNet, FileManager* inFile, QString filePath, QWidget* parent = nullptr);
	~HomeScreen();

	void rollDice();

	int generateRandomNumber(int num);

signals:
	

public slots:
	void handleServerInput(const QJsonObject& inData);

private:
	NetworkManager* networkManager;
	FileManager* fileManager;

	QLabel* ServerStatus;
	QLabel* diceLabel;

	QVBoxLayout* centralLayout;
	QHBoxLayout* row1;
	QHBoxLayout* row2;
	QHBoxLayout* row3;

	QComboBox* diceType;
	QCheckBox* sendToServer;
	QPushButton* rollDicebtn;

	bool isConnected;
};