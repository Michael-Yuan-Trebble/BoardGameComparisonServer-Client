#include "Navigator.h"
#include "ClientApp.h"
#include "HomeScreen.h"
#include "FileSelectorWindow.h"
#include "SettingsWindow.h"

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
	if (clientWindow) clientWindow->hide();
	selectorWindow = new FileSelectorWindow(network, fileManager);
	connect(selectorWindow, &FileSelectorWindow::fileSelected, this, &Navigator::onFileSelected);
	selectorWindow->show();
}

void Navigator::onFileSelected(QString fileName) 
{
	if (selectorWindow) selectorWindow->hide();
	homeScreen = new HomeScreen(network, fileManager, fileName);
	connect(homeScreen, &HomeScreen::goToSettings, this, &Navigator::onSettings);
	homeScreen->show();
}

void Navigator::onSettings(const QString& filePath) 
{
	if (homeScreen) homeScreen->setEnabled(false);

	if (settingsWindow) 
	{
		settingsWindow->raise();
		settingsWindow->activateWindow();
	}

	settingsWindow = new SettingsWindow(network, fileManager, filePath);
	settingsWindow->setAttribute(Qt::WA_DeleteOnClose);

	settingsWindow->setWindowFlag(Qt::Window, true);
	settingsWindow->setWindowFlag(Qt::WindowStaysOnTopHint, true);

	connect(settingsWindow, &SettingsWindow::goBack, this, &Navigator::goBackHome);

	settingsWindow->show();
}

void Navigator::goBackHome()
{
	if (homeScreen) homeScreen->setEnabled(true);
	settingsWindow = nullptr;
}