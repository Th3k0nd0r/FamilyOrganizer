#ifndef VIEW_SINGLEUSERROW_H
#define VIEW_SINGLEUSERROW_H

#include <view.h>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <model_user.h>

class ViewSingleUserRow : public View {

Q_OBJECT

private:
	QLineEdit* nameEdit;
	QLineEdit* userEdit;
	QLineEdit* passEdit;
	QComboBox* userTypeCombo;
	QCheckBox* canCreateUsersCheck;
	QCheckBox* canCreateRemindersCheck;
	QWidget* permissionsContainer;
	QPushButton* updateButton;
	QPushButton* deleteButton;

public:
	ViewSingleUserRow(const ModelUser* user, int userType, QWidget* parent=0);

	void insertIntoGridLayout(QGridLayout* listLayout, int curRow) const;
	QString getName() const;
	QString getUsername() const;
	int getUserType() const;
	ModelUser::Permissions getPermissions() const;

signals:
	void updateUserClicked() const;
	void deleteUserClicked() const;
};
#endif // VIEW_SINGLEUSERROW_H
