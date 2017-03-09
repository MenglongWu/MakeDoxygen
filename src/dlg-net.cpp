#include "dlg-net.h"

DlgNet::DlgNet(QWidget *parent)
	: QDialog(parent)
{
	int frameStyle = 0;


	integerLabel = new QLabel;
	integerLabel->setFrameStyle(frameStyle);
	
	label_ip = new QLabel;
	label_ip->setFrameStyle(frameStyle);	
	label_ip->setText(QString("ip"));

	label_mask = new QLabel;
	label_mask->setFrameStyle(frameStyle);	
	label_mask->setText(QString("mask"));
	
	
	label_gw = new QLabel;
	label_gw->setFrameStyle(frameStyle);
	label_gw->setText(QString("gw"));

	label_dns = new QLabel;
	label_dns->setFrameStyle(frameStyle);
	label_dns->setText(QString("dns"));



	edit_ip = new QLineEdit;
	edit_ip->setText(QString("192.168.1.1"));
	edit_mask = new QLineEdit;
	edit_gw = new QLineEdit;
	edit_dns = new QLineEdit;
	
	QPushButton *btn_ok =    new QPushButton("OK");





	QGridLayout *layout = new QGridLayout;



	layout->setColumnStretch(1, 1);
	layout->setColumnMinimumWidth(1, 250);
	layout->addWidget(label_ip	, 0, 0);
	layout->addWidget(edit_ip	, 0, 1);
	layout->addWidget(label_mask	, 1, 0);
	layout->addWidget(edit_mask	, 1, 1);
	layout->addWidget(label_gw	, 3, 0);
	layout->addWidget(edit_gw	, 3, 1);
	layout->addWidget(label_dns	, 4, 0);
	layout->addWidget(edit_dns	, 4, 1);
	layout->addWidget(btn_ok	, 4, 2);
	connect(btn_ok, SIGNAL(clicked()), this, SLOT(set_net()));


	setLayout(layout);

	setWindowTitle(("Standard Dialogs"));
}

void DlgNet::set_net()
{
	exit(1);
}

