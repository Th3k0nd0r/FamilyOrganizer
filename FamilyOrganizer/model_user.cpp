#include "model_user.h"

#include<QCryptographicHash>
#include <iostream>


ModelUser::ModelUser(const QString& pName, const QString& pUsername, const QString& pPassword, Permissions pUserPermissions) :
	name(pName),
	username(pUsername),
	password(cryptPassword(pPassword)),
	userPermissions(pUserPermissions) {}

ModelUser::~ModelUser() { }

QList<ModelReminder*> ModelUser::getRemindersForMe(const ModelShowcase& showcase) const {
	return showcase.getBaseRemindersForUser(username);
}

void ModelUser::serialize(QXmlStreamWriter& xmlWriter) const {
	xmlWriter.writeStartElement(getModelLabel());
	xmlWriter.writeTextElement("name", name);
	xmlWriter.writeTextElement("username", username);
	xmlWriter.writeTextElement("password", password);
	xmlWriter.writeTextElement("userpermissions", QString::fromStdString(std::to_string(userPermissions)));
	xmlWriter.writeEndElement();
}

void ModelUser::deSerialize(QXmlStreamReader& xmlReader) {
	QXmlStreamReader::TokenType token;
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {

		token = xmlReader.readNext();
		if(token == QXmlStreamReader::StartElement) {
			if(xmlReader.name()=="name")
				name = xmlReader.readElementText();
			else if(xmlReader.name()=="username")
				username = xmlReader.readElementText();
			else if(xmlReader.name()=="password")
				password = xmlReader.readElementText();
			else if(xmlReader.name() == "userpermissions")
				userPermissions =  static_cast<Permissions>(std::stoi(xmlReader.readElementText().toStdString()));

		} else if(token == QXmlStreamReader::EndElement
				   && xmlReader.name() == getModelLabel())
			break;
	}
}

QString ModelUser::cryptPassword(const QString& data) {
	return QString(QCryptographicHash::hash(QByteArray::fromStdString(data.toStdString()),QCryptographicHash::Md5).toHex());
}

ModelUser::Permissions ModelUser::getPermissions() const {
	return userPermissions;
}
QString ModelUser::getName() const {
	return name;
}

QString ModelUser::getUsername() const {
	return username;
}

QString ModelUser::getPassword() const {
	return password;
}

void ModelUser::setName(const QString& pName) {
	name = pName;
}

void ModelUser::setUsername(const QString& pUsername) {
	username = pUsername;
}

void ModelUser::setPassword(const QString& pPassword, const bool& alreadyCrypted) {
	password = (alreadyCrypted ? pPassword : cryptPassword(pPassword));
}

void ModelUser::setPermissions(Permissions pUserPermission) {
	userPermissions = pUserPermission;
}

bool ModelUser::checkLogin(const QString& pPassword) const {
	return (cryptPassword(pPassword) == password);
}
