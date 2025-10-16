#include "Navigator.h"
#include "ClientApp.h"
#include "FileSelectorWindow.h"

Navigator::Navigator(QObject* parent) : QObject(parent) {}

Navigator::~Navigator() {
	clientWindow->deleteLater();
	selectorWindow->deleteLater();
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
}

void Navigator::onFileSelected() {

}