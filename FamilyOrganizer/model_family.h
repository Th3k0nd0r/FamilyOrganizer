#ifndef FAMILY_H
#define FAMILY_H


#include <model_user.h>
#include <QMap>


class ModelFamily : public Model {

private:
	QMap<QString, ModelUser*> users;

public:
	ModelFamily();

	bool addNewUser(ModelUser* pUser);
	ModelUser* getUser(const QString&  pUsername) const;
	void deleteUser(const QString&  pUsername);
	QMap<QString, ModelUser*> getAllUsers() const;
	bool userExists(const QString& pUsername) const;

	//For storage
	virtual QString serialize() const override;
	virtual void deSerialize(const QString& data) override;

	~ModelFamily();
};

#endif // FAMILY_H
