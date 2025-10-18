#pragma once

#include <qobject.h>
#include <memory>

class ClientApp;
class NetworkManager;
class FileSelectorWindow;
class FileManager;
class HomeScreen;

class Navigator : public QObject
{
	Q_OBJECT
public:
	explicit Navigator(QObject* parent = nullptr);
	~Navigator();
	void start(NetworkManager* inNetwork, FileManager* inFile);

public slots:

	void onAdvance();
	void onFileSelected(QString fileName);

private:

	// Screens
	ClientApp* clientWindow;
	FileSelectorWindow* selectorWindow;
	HomeScreen* homeScreen;

	// Objects
	NetworkManager* network;
	FileManager* fileManager;

};