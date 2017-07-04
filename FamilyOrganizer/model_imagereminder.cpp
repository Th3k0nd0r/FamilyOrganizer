#include "model_imagereminder.h"

const QString ModelImageReminder::ModelLabel = "ImageReminder";
ModelImageReminder::ModelImageReminder(int ID, const QString& pTitle, const QString& pDescription,
									   const QString& pCategory, const QString& pDate, const QString& pAuthor,
									   ReminderTarget pTarget,
									   const QString& pImageUrl,
									   const QString& pUsernameSpecificTarget) :
	ModelReminder(ID, pTitle, pDescription,
				  pCategory, pDate, pAuthor,
				  pTarget, pUsernameSpecificTarget),
	imageUrl(pImageUrl),
	imagePixmap(new QPixmap(pImageUrl)) {}


QPixmap* ModelImageReminder::getImage() const {
	return imagePixmap;
}

void ModelImageReminder::serialize(QXmlStreamWriter& xmlWriter) const {
	xmlWriter.writeStartElement(ModelLabel);
	xmlWriter.writeTextElement("id", QString::fromStdString(std::to_string(getID())));
	xmlWriter.writeTextElement("title", getTitle());
	xmlWriter.writeTextElement("description", getDescription());
	xmlWriter.writeTextElement("category", getCategory());
	xmlWriter.writeTextElement("date", getDate());
	xmlWriter.writeTextElement("usernameAuthor", getUsernameAuthor());
	xmlWriter.writeTextElement("target", QString::fromStdString(std::to_string(getTarget())));
	xmlWriter.writeTextElement("usernameSpecificTarget", getUsernameSpecificTarget());
	xmlWriter.writeTextElement("imageUrl", imageUrl );
	xmlWriter.writeEndElement();
}

void ModelImageReminder::deSerialize(QXmlStreamReader& xmlReader) {
	QXmlStreamReader::TokenType token;
	while(!xmlReader.atEnd() && !xmlReader.hasError()) {

		token = xmlReader.readNext();
		if(token == QXmlStreamReader::StartElement) {
			if(xmlReader.name()=="id")
				setID(std::stoi(xmlReader.readElementText().toStdString()));
			else if(xmlReader.name()=="title")
				setTitle(xmlReader.readElementText());
			else if(xmlReader.name()=="description")
				setDescription(xmlReader.readElementText());
			else if(xmlReader.name()=="category")
				setCategory(xmlReader.readElementText());
			else if(xmlReader.name()=="date")
				setDate(xmlReader.readElementText());
			else if(xmlReader.name()=="usernameAuthor")
				setAuthor(xmlReader.readElementText());
			else if(xmlReader.name()=="usernameSpecificTarget")
				setSpecificTarget(xmlReader.readElementText());
			else if(xmlReader.name()=="target")
				setTarget(static_cast<ReminderTarget>(std::stoi(xmlReader.readElementText().toStdString())));
			else if(xmlReader.name()=="imageUrl") {
				imageUrl=xmlReader.readElementText();
				delete imagePixmap;
				imagePixmap = new QPixmap(imageUrl);
			}

		} else if(token == QXmlStreamReader::EndElement
				   && xmlReader.name() == ModelLabel)
			break;
	}
}
