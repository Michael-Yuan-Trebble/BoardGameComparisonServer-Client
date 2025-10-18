#include "Navigator.h"
#include "ClientApp.h"
#include "HomeScreen.h"
#include "FileSelectorWindow.h"

Navigator::Navigator(QObject* parent) : QObject(parent) {}

Navigator::~Navigator()
{
	clientWindow->deleteLater();
	selectorWindow->deleteLater();
	homeScreen->deleteLater();
	network->deleteLater();
	fileManager->deleteLater();
}

void Navigator::start(NetworkManager* inNetwork, FileManager* inFile) 
{
	network = inNetwork;
	fileManager = inFile;

	clientWindow = new ClientApp(network);
	connect(clientWindow, &ClientApp::connectedServer, this, &Navigator::onAdvance);
	clientWindow->show();
}

void Navigator::onAdvance() 
{
	if (clientWindow) 
	{
		clientWindow->hide();
	}
	selectorWindow = new FileSelectorWindow(network, fileManager);
	connect(selectorWindow, &FileSelectorWindow::fileSelected, this, &Navigator::onFileSelected);
	selectorWindow->show();
}

void Navigator::onFileSelected(QString fileName) 
{
	if (selectorWindow) 
	{
		selectorWindow->hide();
	}
	homeScreen = new HomeScreen(network, fileManager, fileName);

	homeScreen->show();
}