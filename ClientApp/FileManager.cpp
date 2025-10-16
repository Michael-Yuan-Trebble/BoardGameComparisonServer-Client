#include "FileManager.h"

FileManager::FileManager(QObject* parent) : QObject(parent)
{

}

FileManager::~FileManager()
{

}

bool FileManager::saveJson(const QString& filePath, const QJsonObject& json)
{
	QString path = filePath;
	if (!path.endsWith(".json", Qt::CaseInsensitive)) path += ".json";

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly)) return false;

	QJsonDocument doc(json);
	file.write(doc.toJson());
	file.close();
	return true;
}

QJsonObject FileManager::loadFile(const QString& filePath) 
{

	QFile file(filePath);
	QJsonObject result;

	if (!file.open(QIODevice::ReadOnly)) return result;

	QByteArray data = file.readAll();
	file.close();

	QJsonDocument doc = QJsonDocument::fromJson(data);
	if (!doc.isNull() && doc.isObject()) result = doc.object();

	return result;
}