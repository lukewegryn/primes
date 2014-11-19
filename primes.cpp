#include <QtWidgets>
#include <QFile>
#include <QDialog>
#include "primes.h"
#include <QListView>
#include <QMenuBar>
#include <QLabel>

Primes::Primes(QWidget *parent)
	: QWidget(parent)
{
	menuBar = new QMenuBar;
	fileMenu = new QMenu(tr("&File"), this);
	startAction = fileMenu->addAction(tr("Start"));
	stopAction = fileMenu->addAction(tr("Stop"));
	exitAction = fileMenu->addAction(tr("E&xit"));
	menuBar->addMenu(fileMenu);

	QLabel *mainLabel = new QLabel;
	QLabel *fromLabel = new QLabel("From: ");
	QLabel *toLabel = new QLabel("To: ");

	fromValue = new QLineEdit;
	toValue = new QLineEdit;
	//fromValue->setAlignment(Qt::AlignLeft);
	//toValue->setAlignment(Qt::AlignLeft);

	mainLabel->setText("How many primes numbers are there from?");

	connect(exitAction, SIGNAL(triggered()), this, SLOT(exitClicked()));
	connect(startAction, SIGNAL(triggered()), this, SLOT(startClicked()));
	connect(stopAction, SIGNAL(triggered()), this, SLOT(stopClicked()));

	displayListView = new QListView();
	QPushButton *exitButton = createButton(tr("Exit"),SLOT(exitClicked()));
	QPushButton *startButton = createButton(tr("Start"), SLOT(startClicked()));
	QPushButton *stopButton = createButton(tr("Stop"), SLOT(stopClicked()));

	QGridLayout *mainLayout = new QGridLayout;
	//mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	//mainLayout->addWidget(displayListView, 0,0,1,12);
	mainLayout->setMenuBar(menuBar);
	mainLayout->addWidget(mainLabel,1,0,1,8);
	//add input fields
	mainLayout->addWidget(fromLabel,2,0,1,2);
	mainLayout->addWidget(fromValue,2,2,1,3);
	mainLayout->addWidget(toLabel,  2,6,1,3);
	mainLayout->addWidget(toValue,  2,7,1,3);

	mainLayout->addWidget(displayListView,3,0,1,12);
	mainLayout->addWidget(startButton,4,0,1,4);
	mainLayout->addWidget(stopButton, 4,4,1,4);
	mainLayout->addWidget(exitButton, 4,8,1,4);

	//connect(signalMapper, SIGNAL(mapped(QString)), this, SIGNAL(clicked(QString)));
	setLayout(mainLayout);

	setWindowTitle(tr("Primes"));
}

QPushButton *Primes::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}

void Primes::exitClicked()
{
	this->close();
}

void Primes::startClicked()
{

}

void Primes::stopClicked()
{

}

