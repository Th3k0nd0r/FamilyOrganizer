#include "model_family.h"

#include <model_parentuser.h>
#include <model_childuser.h>
#include <model_guestuser.h>
#include <QXmlStreamWriter>

ModelFamily::ModelFamily() : Model("Family") {}


bool ModelFamily::addNewUser(ModelUser *pUser) {
	if(users.contains(pUser->getUsername()))
		return false;
	users.insert(pUser->getUsername(), pUser);
	return true;
}

void ModelFamily::deleteUser(const QString&  pUsername) {
	users.remove(pUsername);
}

ModelUser* ModelFamily::getUser(const QString& pUsername) const {
	return users.value(pUsername, nullptr);
}

QMap<QString, ModelUser*> ModelFamily::getAllUsers() const {
	return users;
}

QString ModelFamily::serialize() const {
	QString result("");
	QXmlStreamWriter xmlWriter(&result);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement(getModelNameFile());

	for(auto it=users.constBegin();it!=users.constEnd(); ++it)
		(*it)->serialize(xmlWriter);

	xmlWriter.writeEndElement();
	xmlWriter.writeEndDocument();
	return result;
}

void ModelFamily::deSerialize(const QString& data) {
    ModelUser* currentUser=nullptr;
	users.clear();

	QXmlStreamReader xmlReader(data);
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {
		QXmlStreamReader::TokenType token = xmlReader.readNext();

		if(token == QXmlStreamReader::StartDocument)
			continue;


		if(token == QXmlStreamReader::StartElement
			&& xmlReader.name() != "Family") {

			if(xmlReader.name()==ModelParentUser::ModelLabel)
				currentUser = new ModelParentUser();
			else if(xmlReader.name()==ModelChildUser::ModelLabel)
				currentUser = new ModelChildUser();
			else if(xmlReader.name()==ModelGuestUser::ModelLabel)
				currentUser = new ModelGuestUser();

			currentUser->deSerialize(xmlReader);
			addNewUser(currentUser);
            currentUser=nullptr;
		}
	}
}

bool ModelFamily::userExists(const QString &pUsername) const {
	return users.contains(pUsername);
}

ModelFamily::~ModelFamily() {
	//Deep destructor
	QMap<QString, ModelUser*>::const_iterator it = users.constBegin();
	for(;it!=users.constEnd(); ++it)
		delete *it;
}
