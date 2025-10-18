#include "HomeScreen.h"
#include "NetworkManager.h"

HomeScreen::HomeScreen(NetworkManager* inNet, FileManager* inFile, QString filePath, QWidget* parent) : QMainWindow(parent) 
{
	networkManager = inNet;

	QWidget* centralWidget = new QWidget(this);

	centralLayout = new QVBoxLayout(centralWidget);

	row1 = new QHBoxLayout(centralWidget);
	row2 = new QHBoxLayout(centralWidget);
	row3 = new QHBoxLayout(centralWidget);

	// Connect the network manager's disconnect function to change this
	isConnected = inNet->running;

	QString connectedStatus = isConnected ? "Server Online" : "Server Offline";

	ServerStatus = new QLabel(connectedStatus,centralWidget);

	row1->addWidget(ServerStatus);

	diceType = new QComboBox(centralWidget);
	int dice[7] = {4,6,8,10,12,20,100};

	for (int i = 0; i < 7; i++) diceType->addItem(QString::number(dice[i]));

	rollDicebtn = new QPushButton("Roll", centralWidget);

	connect(rollDicebtn, &QPushButton::clicked, this, &HomeScreen::rollDice);

	sendToServer = new QCheckBox("Send to Server", this);
	sendToServer->setChecked(true);

	row2->addWidget(diceType);
	row2->addWidget(rollDicebtn);

	diceLabel = new QLabel("Not Rolled", centralWidget);
	row3->addWidget(diceLabel);

	centralLayout->addLayout(row1);
	centralLayout->addLayout(row2);
	centralLayout->addLayout(row3);

	setCentralWidget(centralWidget);

	connect(inNet, &NetworkManager::messageRecieved, this, &HomeScreen::handleServerInput);

	resize(800, 800);
}

HomeScreen::~HomeScreen() {}

void HomeScreen::rollDice() 
{
	int num = diceType->currentText().toInt();
	int ranNum = generateRandomNumber(num);

	diceLabel->setText(QString::number(ranNum));

	if (!sendToServer->isChecked()) return;

	QString msg = QString("ROLL %1 %2").arg(num).arg(ranNum);
	QByteArray data = msg.toUtf8();

	if (!networkManager->sendData(data.constData(),data.size())) 
	{
		QMessageBox::warning(
			this,
			"Warning",
			"Warning, failed to send data",
			QMessageBox::Ok
		);
	}
	return;
}

int HomeScreen::generateRandomNumber(int num) 
{
	int randomNum = QRandomGenerator::global()->bounded(1, num + 1);
	return randomNum;
}

void HomeScreen::handleServerInput(const QJsonObject& inData)
{
	if (inData["result"].toBool()) 
	{
		QMessageBox::warning(
			this,
			"Warning",
			"true",
			QMessageBox::Ok
		);
	}
	else 
	{
		QMessageBox::warning(
			this,
			"Warning",
			"false",
			QMessageBox::Ok
		);
	}

	inData["serverResult"].toInt();
}