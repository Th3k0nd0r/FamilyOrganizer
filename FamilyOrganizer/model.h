#ifndef MODELSERIALIZABLE_H
#define MODELSERIALIZABLE_H

#include<QString>
#include<QFile>

class Model {

private:
	static const QString STORAGE_DIRNAME;
	static const QString STORAGE_FILE_EXTENSION;
	QFile storageFile;
	const QString modelNameFile;

public:
	Model(const QString& pModelName);

	bool saveToFile();
	bool readFromFile();

    QString getModelNameFile() const;

	virtual QString serialize() const = 0;
	virtual void deSerialize(const QString& data) = 0;

	virtual ~Model() = default;
};

#endif // MODELSERIALIZABLE_H
