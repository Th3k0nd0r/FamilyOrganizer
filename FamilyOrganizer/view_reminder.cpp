#include "view_reminder.h"
#include <iostream>
#include <model_imagereminder.h>

ViewReminder::ViewReminder(ModelReminder* pModel, QWidget* parent) :
	View(parent),
	title(new QLabel(finalTitleText(pModel->getTitle()), this)),
	imageLabel(new QLabel("Immagine non disponibile", this)),
	description(new QLabel(finalDescriptionText(pModel->getDescription()),this)),
	categoryLabel(new QLabel(finalCategoryText(pModel->getCategory()),this)),
	authorLabel(new QLabel(finalAuthorText(pModel->getUsernameAuthor()), this)),
	targetLabel(new QLabel(finalTargetText(pModel->getTarget()==1 ?
											   pModel->getUsernameSpecificTarget():
												ModelTargetType::targetToString(pModel->getTarget())), this)),
	dateLabel(new QLabel(pModel->getDate(), this)),
	layout(new QGridLayout(this)),
	model(pModel),
	shadowEffect(new QGraphicsDropShadowEffect) {

	//checking if it's an imageReminder
	ModelImageReminder* pModelImage = dynamic_cast<ModelImageReminder*>(pModel);
	if(pModelImage)
		imageLabel->setPixmap(*pModelImage->getImage());
	else
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	imageLabel->setMaximumHeight(450);

	dateLabel->setAlignment(Qt::AlignHCenter);
	title->setAlignment(Qt::AlignHCenter);
	imageLabel->setAlignment(Qt::AlignHCenter);
	imageLabel->setScaledContents(true);
	description->setAlignment(Qt::AlignHCenter);
	description->setWordWrap(true);
	targetLabel->setAlignment(Qt::AlignRight);
	authorLabel->setAlignment(Qt::AlignLeft);
	categoryLabel->setAlignment(Qt::AlignHCenter);

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


	title->setStyleSheet("padding:15px;"
						 "color: white;"
						 "border-radius: 0px; border-bottom: 2px solid rgba(4, 4, 4, 0.22);"
						 "font-weight: 500;"
						 "position: absolute;"
						 "width: 80%;"
						 "left: 0;"
						 "right: 0;"
						 "margin: 0 auto;"
						"top: 7px;");
	title->setMaximumHeight(53);
	dateLabel->setStyleSheet("font-size: 15px;background-color:#1D2D44;");
	dateLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	description->setStyleSheet("padding:0px; margin: 30px 0; margin-top:0px;");
	authorLabel->setStyleSheet("padding:0px; font-weight:400; font-size: 15px;");
	categoryLabel->setStyleSheet("padding:0px; font-weight:400; text-decoration: underline; font-size: 15px;");
	targetLabel->setStyleSheet("padding:0px; font-weight:400; font-size: 15px;margin-left:-100px;");
	targetLabel->setMaximumHeight(35);
	setStyleSheet("position: relative;"
				  "opacity: 0;"
				  "text-align: center;"
				  "padding: 18px;"
				  "margin-bottom:10px;"
				  "font-size: 19px; font-weight: 300;"
				  "border-radius: 5px;"
				  "background-color: #00648f;"
				  "color: white;");

	layout->addWidget(dateLabel, 0, 0, 1, 4);
	layout->addWidget(title, 1, 0, 1, 4);

	if(pModelImage) {
		layout->addWidget(imageLabel, 2, 0, 2, 4);
		layout->addWidget(description, 4, 0, 1, 4);
	} else {
		layout->addWidget(description, 2, 0, 3, 4);
		imageLabel->hide();
	}

	layout->addWidget(authorLabel, 5, 0);
	layout->addWidget(categoryLabel,5, 1, 1, 2);
	layout->addWidget(targetLabel, 5, 3);
	layout->setContentsMargins(10,10,10,10);

	shadowEffect->setColor(QColor::fromRgb(185,185,185));
	shadowEffect->setBlurRadius(20);
	shadowEffect->setXOffset(0);
	shadowEffect->setYOffset(9);
    setGraphicsEffect(shadowEffect);
	setMaximumWidth(500);
	setMinimumWidth(500);
	setLayout(layout);
}

QString ViewReminder::finalTitleText(const QString& data) const {
	return data.toUpper();
}

QString ViewReminder::finalDescriptionText(const QString& data) const {
	return data;//"<b>"+data+"</b>";
}

QString ViewReminder::finalCategoryText(const QString& data) const {
	return "<i>"+data+"</i>";
}

QString ViewReminder::finalAuthorText(const QString& data) const {
	return "Da: "+data;//+"</i>";
}

QString ViewReminder::finalTargetText(const QString& data) const {
	return "Per: "+data;
}
