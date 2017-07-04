#ifndef MODEL_IMAGEREMINDER_H
#define MODEL_IMAGEREMINDER_H

#include <model_reminder.h>
#include <QPixmap>

class ModelImageReminder : public ModelReminder {

private:

	QString imageUrl;
    QPixmap*  imagePixmap;


public:
    const static QString ModelLabel;

	ModelImageReminder() = default;
	ModelImageReminder(int ID, const QString& pTitle, const QString& pDescription,
					   const QString& pCategory, const QString& pDate,
					   const QString& pAuthor, ReminderTarget pTarget, const QString& imagUrl,
						const QString& pUsernameSpecificTarget = "-");
	QPixmap* getImage() const;

	virtual void serialize(QXmlStreamWriter&) const;
	virtual void deSerialize(QXmlStreamReader&);
};

#endif // MODEL_IMAGEREMINDER_H
