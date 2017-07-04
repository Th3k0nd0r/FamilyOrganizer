#ifndef VIEW_SINGLEREMINDERROW_H
#define VIEW_SINGLEREMINDERROW_H

#include <view.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <model_reminder.h>

class ViewSingleReminderRow : public View {

Q_OBJECT

private:
	QLineEdit* idEdit;
	QLineEdit* titleEdit;
	QLineEdit* descriptionEdit;
	QLineEdit* categoryEdit;
	QLineEdit* authorEdit;
	QComboBox* targetCombo;
	QLineEdit* specificTargetEdit;
	QPushButton* updateButton;
	QPushButton* deleteButton;

public:
    ViewSingleReminderRow(const ModelReminder* reminder, QWidget* parent=0);

	void insertIntoGridLayout(QGridLayout* listLayout, int curRow) const;
	int getID() const;
	QString getTitle() const;
	QString getDescription() const;
	QString getCategory() const;
	QString getAuthor() const;
	int getTarget() const;
	QString getSpecificTarget() const;

private slots:
	void onTargetChanged(int idx);

signals:
	void updateReminderClicked() const;
	void deleteReminderClicked() const;
};

#endif // VIEW_SINGLEREMINDERROW_H
