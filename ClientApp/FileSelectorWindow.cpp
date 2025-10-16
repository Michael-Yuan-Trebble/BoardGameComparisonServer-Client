#include "FileSelectorWindow.h"

FileSelectorWindow::FileSelectorWindow(NetworkManager* inNet, FileManager* inFile, QWidget* parent)
	: QMainWindow(parent)
{
	network = inNet;
	fileManager = inFile;

	QWidget* CentralWidget = new QWidget(this);

	setCentralWidget(CentralWidget);

	MainLayout = new QVBoxLayout(CentralWidget);

	loadFilebtn = new QPushButton(CentralWidget);
	createFilebtn = new QPushButton(CentralWidget);

	QHBoxLayout* layout1 = new QHBoxLayout(CentralWidget);

	layout1->addWidget(loadFilebtn);
	layout1->addWidget(createFilebtn);

	MainLayout->addLayout(layout1);
	
}

FileSelectorWindow::~FileSelectorWindow() 
{

}

void FileSelectorWindow::createFile() 
{
	QString filePath = QFileDialog::getSaveFileName(
		this,
		"Create JSON File",
		"",
		"JSON Files (*.json)"
	);

	if (filePath.isEmpty()) return;
	

	if (!filePath.endsWith(".json", Qt::CaseInsensitive)) filePath += ".json";

	QFile file(filePath);
	if (!file.exists()) return;
	
}

void FileSelectorWindow::loadFile()
{
	QString fileName = QFileDialog::getOpenFileName(
		this,
		"Load JSON File",
		"",
		"JSON Files (*.json)"
	);

	if (fileName.isEmpty()) return;

	QFile file(fileName);
	if (!file.exists()) return;
}