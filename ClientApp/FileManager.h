#pragma once

#include <qobject.h>
#include <qfiledialog.h>
#include <qjsonobject.h>

class FileManager : public QObject
{
	Q_OBJECT

public:
	FileManager(QObject* parent = nullptr);
	~FileManager();

public slots:
	QJsonObject loadFile(const QString& filePath);

	bool saveJson(const QString& filePath, const QJsonObject& json);

private:

};