#pragma once

#include <QtWidgets/qmainwindow.h>

class NetworkManager;
class FileManager;

class HomeScreen : public QMainWindow 
{
	Q_OBJECT
public:
	HomeScreen(NetworkManager* inNet, FileManager* inFile, QWidget* parent = nullptr);
	~HomeScreen();

signals:


private:
	NetworkManager* networkManager;
	FileManager* fileManager;
};