#ifndef VIEW_PAGE_NEWREMINDER_H
#define VIEW_PAGE_NEWREMINDER_H

#include <view_page.h>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>

class ViewPageNewReminder : public ViewPage {

Q_OBJECT

private:
	QVBoxLayout* layout;

	QWidget* formContainer;
	QFormLayout* formLayout;
	QLineEdit* titleEdit;
	QTextEdit* descriptionEdit;
	QLineEdit* categoryEdit;
	QComboBox* targetCombo;
	QLineEdit* specificTargetEdit;
	QComboBox* typeCombo;
	QString imageUrl;
	QFileDialog* imageSelector;
	QPushButton* imageSelectorButton;
	QPushButton* submitButton;

private slots:
	void onTargetChanged(int idx);
	void onTypeChanged(int idx);
	void onImageSelectorButtonClicked();
	void onImageSelectorFinished(const QString& s);

public:
	ViewPageNewReminder(QWidget* parent=0);
	QString getTitle() const;
	QString getDescription() const;
	QString getCategory() const;
	int getTargetType() const;
	QString getSpecificTargetUsername() const;
	int getReminderType() const;
	QString getImageUrl() const;

signals:
	void formSubmitted() const;
};

#endif // VIEW_PAGE_NEWREMINDER_H
