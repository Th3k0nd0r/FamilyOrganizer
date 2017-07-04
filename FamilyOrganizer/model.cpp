#include "model.h"
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

const QString Model::STORAGE_DIRNAME = "data";
const QString Model::STORAGE_FILE_EXTENSION= ".xml";


Model::Model(const QString& pModelName)
	: storageFile(QCoreApplication::applicationDirPath() + "/" + STORAGE_DIRNAME + "/" + pModelName + STORAGE_FILE_EXTENSION),
	   modelNameFile(pModelName) {}

bool Model::saveToFile() {
	QDir storageDir(QCoreApplication::applicationDirPath() + "/" + STORAGE_DIRNAME);
	if(!storageDir.exists())
		storageDir.mkdir(".");

	if (!storageFile.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;
	QTextStream out(&storageFile);
    out.setCodec("UTF-8");
	out << serialize();
	storageFile.close();

	return true;
}

bool Model::readFromFile() {
	QString result("");
	if(!storageFile.exists() || !storageFile.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;
	QTextStream in(&storageFile);
    in.setCodec("UTF-8");
	while(!in.atEnd())
		result.append(in.readLine());
	storageFile.close();
	deSerialize(result);
	return true;
}

QString Model::getModelNameFile() const {
	return modelNameFile;
}
