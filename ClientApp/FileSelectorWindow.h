#pragma once

#include <qobject.h>
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qjsonobject.h>
#include <qbytearray.h>
#include <qmessagebox.h>
#include <qjsondocument.h>
#include "NetworkManager.h"
#include "FileManager.h"

class FileSelectorWindow : public QMainWindow 
{
	Q_OBJECT
public:
	FileSelectorWindow(NetworkManager* inNet, FileManager* inFile, QWidget* parent = nullptr);
	~FileSelectorWindow();

signals:
	void fileSelected(QString fileName);

private:

	QJsonObject obj;

	NetworkManager* network;
	FileManager* fileManager;

	QPushButton* loadFilebtn;
	QPushButton* createFilebtn;

	QVBoxLayout* MainLayout;

	void createFile();

	void loadFile();
};