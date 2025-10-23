#include "FileSelectorWindow.h"

FileSelectorWindow::FileSelectorWindow(NetworkManager* inNet, FileManager* inFile, QWidget* parent)
	: QMainWindow(parent)
{
	setWindowTitle("File Selection");

	network = inNet;
	fileManager = inFile;

	QWidget* CentralWidget = new QWidget(this);

	setCentralWidget(CentralWidget);

	MainLayout = new QVBoxLayout(CentralWidget);

	loadFilebtn = new QPushButton(CentralWidget);
	loadFilebtn->setText("Load File");
	createFilebtn = new QPushButton(CentralWidget);
	createFilebtn->setText("Create File");

	connect(loadFilebtn, &QPushButton::clicked, this, &FileSelectorWindow::loadFile);
	connect(createFilebtn, &QPushButton::clicked, this, &FileSelectorWindow::createFile);

	QHBoxLayout* layout1 = new QHBoxLayout(CentralWidget);

	layout1->addWidget(loadFilebtn);
	layout1->addWidget(createFilebtn);

	MainLayout->addLayout(layout1);
	
	resize(800, 800);
}

FileSelectorWindow::~FileSelectorWindow() {}

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
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) 
	{
		QMessageBox::warning(
			this,
			"Warning",
			"Failed to create or open file",
			QMessageBox::Ok
		);
		return;
	}

	QJsonObject result = fileManager->loadFile(filePath);
	result["list"] = {};

	if (!fileManager->saveJson(filePath, result)) 
	{
		QMessageBox::warning(
			this,
			"Warning",
			"Failed to save file",
			QMessageBox::Ok
		);
		return;
	}

	emit fileSelected(filePath);
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

	emit fileSelected(fileName);
}