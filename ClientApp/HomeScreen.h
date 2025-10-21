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
#include <qjsonarray.h>
#include <qjsonobject.h>
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
	void goToSettings(const QString& filePath);

public slots:
	void handleServerInput(const QJsonObject& inData);

private:
	void readJson(const QString& filePath);

	NetworkManager* networkManager;
	FileManager* fileManager;

	QJsonObject file;

	QLabel* ServerStatus;
	QLabel* diceLabel;

	QVBoxLayout* centralLayout;
	QHBoxLayout* row1;
	QHBoxLayout* row2;
	QHBoxLayout* row3;
	QHBoxLayout* row4;

	QComboBox* diceType;
	QComboBox* diceAdd;

	QCheckBox* sendToServer;
	QPushButton* rollDicebtn;
	QPushButton* settingsbtn;

	bool isConnected;
};