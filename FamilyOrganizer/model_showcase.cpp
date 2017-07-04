#include "model_showcase.h"
#include <QXmlStreamWriter>
#include <string>
#include <iostream>
#include <model_imagereminder.h>


ModelShowcase::ModelShowcase() : Model("Showcase"), lastIDAdded(0) {}

void ModelShowcase::addNewReminder(ModelReminder *r) {
	reminders.push_back(r);
	lastIDAdded = r->getID();
}

void ModelShowcase::deleteReminder(const int& ID) {
	ModelReminder* reminderToDelete = getReminderById(ID);
	if(reminderToDelete)
		reminders.removeAll(reminderToDelete);
}

ModelReminder* ModelShowcase::getReminderById(const int& pID) const {
	for(auto it=reminders.constBegin(); it!=reminders.constEnd();++it)
		if((*it)->getID() == pID)
			return *it;
	return 0;
}

QList<ModelReminder*> ModelShowcase::getRemindersByTarget(ReminderTarget pTarget) const {
	if(pTarget == ReminderTarget::SpecificUser)
		return QList<ModelReminder*>();
	QList<ModelReminder*> result;
	for(auto it = reminders.constBegin(); it!=reminders.constEnd();++it)
		if((*it)->getTarget() == pTarget)
			result.push_front(*it);

	return result;
}

QList<ModelReminder*> ModelShowcase::getRemindersBySpecificTarget(const QString& pUsername) const {
	QList<ModelReminder*> result;
	for(auto it = reminders.constBegin(); it!=reminders.constEnd();++it)
		if((*it)->getTarget() == ReminderTarget::SpecificUser &&
		   (*it)->getUsernameSpecificTarget() == pUsername)
			result.push_front(*it);

	return result;
}

QList<ModelReminder*> ModelShowcase::getRemindersByCategory(const QString& pCategory) const {

	QList<ModelReminder*> result;
	for(auto it=reminders.constBegin(); it!=reminders.constEnd(); ++it)
		if((*it)->getCategory()==pCategory)
			result.push_front(*it);
	return result;
}

QList<ModelReminder*> ModelShowcase::getRemindersByAuthor(const QString &pUsername) const {
	QList<ModelReminder*> result;
	for(auto it=reminders.constBegin(); it!=reminders.constEnd(); ++it)
		if((*it)->getUsernameAuthor()==pUsername)
			result.push_front(*it);

	return result;
}

QList<ModelReminder*> ModelShowcase::getBaseRemindersForUser(const QString& pUsername) const {
	QList<ModelReminder*> result;

	for(auto it = reminders.constBegin(); it!=reminders.constEnd();++it)
		if(((*it)->getTarget()==ReminderTarget::SpecificUser &&
			(*it)->getUsernameSpecificTarget() == pUsername) ||
			(*it)->getTarget() == ReminderTarget::AllUsers	)
			result.push_front(*it);

	return result;
}

QList<ModelReminder*> ModelShowcase::getAllReminders() const {
	return reminders;
}

QString ModelShowcase::serialize() const {

	QString result("");
	QXmlStreamWriter xmlWriter(&result);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement(getModelNameFile());
	for(auto it=reminders.constBegin();it!=reminders.constEnd(); ++it)
		(*it)->serialize(xmlWriter);

	xmlWriter.writeEndElement();
	xmlWriter.writeEndDocument();
	return result;
}

void ModelShowcase::deSerialize(const QString& data) {
	reminders.clear();
	ModelReminder* currentReminder=0;

	QXmlStreamReader xmlReader(data);
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {
		QXmlStreamReader::TokenType token = xmlReader.readNext();

		if(token == QXmlStreamReader::StartDocument)
			continue;


		if(token == QXmlStreamReader::StartElement
				&& xmlReader.name() != "Showcase") {

			if(xmlReader.name()==ModelReminder::ModelLabel)
				currentReminder=new ModelReminder();
			else if(xmlReader.name()==ModelImageReminder::ModelLabel)
				currentReminder=new ModelImageReminder();

			currentReminder->deSerialize(xmlReader);
			addNewReminder(currentReminder);
			currentReminder=0;
		}
	}
}

int ModelShowcase::getLastID() const {
	return lastIDAdded;
}

ModelShowcase::~ModelShowcase() {
	for(auto it=reminders.constBegin(); it!=reminders.constEnd(); ++it)
		delete *it;
}
