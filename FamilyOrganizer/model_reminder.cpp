#include "model_reminder.h"

const QString ModelReminder::ModelLabel = "TextReminder";
ModelReminder::ModelReminder(int pID, const QString& pTitle, const QString& pDescription,
				   const QString& pCategory, const QString& pDate, const QString& pAuthor,
				   ReminderTarget pTarget, const QString& pUsernameSpecificTarget) :
	ID(pID), title(pTitle), description(pDescription), category(pCategory), date(pDate),
	usernameAuthor(pAuthor), target(pTarget), usernameSpecificTarget(pUsernameSpecificTarget) { }



int ModelReminder::getID() const {
	return ID;
}

QString ModelReminder::getTitle() const {
	return title;
}

QString ModelReminder::getDescription() const {
	return description;
}

QString ModelReminder::getCategory() const {
	return category;
}

QString ModelReminder::getDate() const {
	return date;
}

ReminderTarget ModelReminder::getTarget() const {
	return target;
}

QString ModelReminder::getUsernameSpecificTarget() const {
	return usernameSpecificTarget;
}

QString ModelReminder::getUsernameAuthor() const {
	return usernameAuthor;
}

void ModelReminder::setID(int pID) {
	ID = pID;
}

void ModelReminder::setTitle(const QString& pTitle) {
	title=pTitle;
}

void ModelReminder::setDescription(const QString& pDescription) {
	description=pDescription;
}

void ModelReminder::setCategory(const QString& pCategory) {
	category = pCategory;
}

void ModelReminder::setDate(const QString& pDate) {
	date = pDate;
}

void ModelReminder::setAuthor(const QString& pAuthor) {
	usernameAuthor = pAuthor;
}

void ModelReminder::setTarget(ReminderTarget pTarget) {
	target = pTarget;
}

void ModelReminder::setSpecificTarget(const QString& pUsername) {
	usernameSpecificTarget = pUsername;
}

void ModelReminder::serialize(QXmlStreamWriter& xmlWriter) const {
	xmlWriter.writeStartElement(ModelLabel);
	xmlWriter.writeTextElement("id", QString::fromStdString(std::to_string(ID)));
	xmlWriter.writeTextElement("title", title);
	xmlWriter.writeTextElement("description", description);
	xmlWriter.writeTextElement("category", category);
	xmlWriter.writeTextElement("date", date);
	xmlWriter.writeTextElement("usernameAuthor", usernameAuthor);
	xmlWriter.writeTextElement("target", QString::fromStdString(std::to_string(target)));
	xmlWriter.writeTextElement("usernameSpecificTarget", usernameSpecificTarget);
	xmlWriter.writeEndElement();
}

void ModelReminder::deSerialize(QXmlStreamReader& xmlReader) {
	QXmlStreamReader::TokenType token;
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {

		token = xmlReader.readNext();
		if(token == QXmlStreamReader::StartElement) {
			if(xmlReader.name()=="id")
				ID = std::stoi(xmlReader.readElementText().toStdString());
			else if(xmlReader.name()=="title")
				title = xmlReader.readElementText();
			else if(xmlReader.name()=="description")
				description = xmlReader.readElementText();
			else if(xmlReader.name()=="category")
				category = xmlReader.readElementText();
			else if(xmlReader.name()=="date")
				date = xmlReader.readElementText();
			else if(xmlReader.name()=="usernameAuthor")
				usernameAuthor = xmlReader.readElementText();
			else if(xmlReader.name()=="usernameSpecificTarget")
				usernameSpecificTarget = xmlReader.readElementText();
			else if(xmlReader.name()=="target")
				target = static_cast<ReminderTarget>(std::stoi(xmlReader.readElementText().toStdString()));
		} else if(token == QXmlStreamReader::EndElement
				   && xmlReader.name() == ModelLabel)
			break;
	}
}
