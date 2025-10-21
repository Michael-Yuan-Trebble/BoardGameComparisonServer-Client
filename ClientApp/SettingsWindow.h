#pragma once

#include <qobject.h>
#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qlabel.h>
#include <qjsonobject.h>
#include <qbytearray.h>
#include <qmessagebox.h>
#include <qjsondocument.h>
#include "NetworkManager.h"
#include "FileManager.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT
public:
	SettingsWindow(NetworkManager* inNet, FileManager* inFile, const QString& filePath, QWidget* parent = nullptr);
	~SettingsWindow();

signals:
	void goBack();

private:

	QJsonObject file;

	NetworkManager* network;
	FileManager* fileManager;

	QPushButton* loadFilebtn;
	QPushButton* createFilebtn;

	QVBoxLayout* MainLayout;

	void createFile();

	void loadFile();
	void closeEvent(QCloseEvent* event);
};