#ifndef VIEW_REMINDER_H
#define VIEW_REMINDER_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QGraphicsDropShadowEffect>
#include <model_reminder.h>
#include <view.h>

class ViewReminder : public View {

private:
	QLabel* title;

	QLabel* imageLabel;
	QLabel* description;

	QLabel* categoryLabel;
	QLabel* authorLabel;
	QLabel* targetLabel;
	QLabel* dateLabel;

	QGridLayout* layout;
	ModelReminder* model;
	QGraphicsDropShadowEffect* shadowEffect;


public:
	ViewReminder(ModelReminder* pModel, QWidget* parent = 0);

	QString finalTitleText(const QString& data) const;
	QString finalDescriptionText(const QString& data) const;
	QString finalCategoryText(const QString& data) const;
	QString finalAuthorText(const QString& data) const;
	QString finalTargetText(const QString& data) const;
};

#endif // VIEW_REMINDER_H
