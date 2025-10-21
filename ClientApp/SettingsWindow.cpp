#include "SettingsWindow.h"
#include "FileManager.h"

SettingsWindow::SettingsWindow(NetworkManager* inNet, FileManager* inFile, const QString& filePath, QWidget* parent) 
	: QMainWindow(parent)
{
	setWindowTitle("Settings");

	network = inNet;
	fileManager = inFile;

	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	file = fileManager->loadFile(filePath);

	MainLayout = new QVBoxLayout(centralWidget);

	QLabel* something = new QLabel(centralWidget);
	MainLayout->addWidget(something);
}

SettingsWindow::~SettingsWindow() {}

void SettingsWindow::closeEvent(QCloseEvent* event)
{
	emit goBack();
	QMainWindow::closeEvent(event);
}