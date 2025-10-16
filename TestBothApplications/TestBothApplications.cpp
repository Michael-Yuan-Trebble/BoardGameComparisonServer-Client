#include "TestBothApplications.h"

TestBothApplications::TestBothApplications(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	startBoth();
}

TestBothApplications::~TestBothApplications()
{}


void TestBothApplications::startBoth() 
{
	QProcess* serverProc = new QProcess(this);
	QProcess* clientProc = new QProcess(this);

	serverProc->start("ServerApp.exe");

	connect(serverProc, &QProcess::readyReadStandardOutput, this, [serverProc]() {
		QByteArray out = serverProc->readAllStandardOutput();
		qDebug() << "Server says:" << out;
		});

	clientProc->start("ClientApp.exe");

	if (!serverProc->waitForStarted())
	{
		qDebug() << "Failed to start Server";
	}

	if (!clientProc->waitForStarted())
	{
		qDebug() << "Failed to start Client";
	}
}