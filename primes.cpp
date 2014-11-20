#include <QtWidgets>
#include <QFile>
#include <QDialog>
#include "primes.h"
#include <QListView>
#include <QMenuBar>
#include <QLabel>
#include <pthread.h>
#include <stringListModel.h>
#include <QProgressBar>
#include <QMutex>
#include <QStreamThreaded.h>

long long int lowerBound;
long long int upperBound;
long long int currentPrime;

struct parentVar {
	Primes* parentPointer;
};

parentVar parentStruct;

QMutex mutex;

 void Primes::appendToModel(QString value)
 {
 	int row = listModel->rowCount();
	listModel->insertRows(row, 1);
	QModelIndex index = listModel->index(row);
	listModel->setData(index,value);
	displayListView->setCurrentIndex(index);
 }

void Primes::emitUpdateModel(QString value)
{
	emit this->updateModel(value);
}
void* runEratosthenesSieve(void *arg) {
		QOUT("A" << endl);
      if(lowerBound < 2) lowerBound = 2;
      long long int upperBoundSquareRoot = (long long int)sqrt((double)upperBound);
      bool *isComposite = new bool[upperBound + 1];
      memset(isComposite, 0, sizeof(bool) * (upperBound + 1));
      for (int m = 2; m <= upperBoundSquareRoot; m++) {
            if (!isComposite[m]) {
            			if(m > lowerBound){
            				parentStruct.parentPointer->emitUpdateModel(QString::number(m));
            				QOUT("D" << endl);
                  			}
                  for (int k = m * m; k <= upperBound; k += m)
                        isComposite[k] = true;
            }
      }
      for (int m = upperBoundSquareRoot; m <= upperBound; m++)
            if (!isComposite[m]){
            	if(m > lowerBound){
            		parentStruct.parentPointer->emitUpdateModel(QString::number(m));
              }
              }
      delete [] isComposite;
      return 0;
}

Primes::Primes(QWidget *parent)
	: QWidget(parent)
{
	parentStruct.parentPointer = this;
	QOUT(this << "Thread Connect" <<endl);
	connect(this, SIGNAL(updateModel(QString)), this, SLOT(appendToModel(QString)), Qt::QueuedConnection);
	listModel = new StringListModel(primeList,this);//(this);
	displayListView = new QListView;//(this);
	displayListView->setModel(listModel);

	menuBar = new QMenuBar(this);
	fileMenu = new QMenu(tr("&File"), this);
	startAction = fileMenu->addAction(tr("Start"));
	stopAction = fileMenu->addAction(tr("Stop"));
	exitAction = fileMenu->addAction(tr("E&xit"));
	menuBar->addMenu(fileMenu);

	progressBar = new QProgressBar;
	progressBar->setVisible(false);

	QLabel *mainLabel = new QLabel;
	QLabel *fromLabel = new QLabel("From: ");
	QLabel *toLabel = new QLabel("To: ");
	QLabel *numberOfPrimes = new QLabel("Number of Primes: ");

	fromValue = new QLineEdit;
	toValue = new QLineEdit;
	//fromValue->setAlignment(Qt::AlignLeft);
	//toValue->setAlignment(Qt::AlignLeft);

	mainLabel->setText("How many primes numbers are there?");
	connect(exitAction, SIGNAL(triggered()), this, SLOT(exitClicked()));
	connect(startAction, SIGNAL(triggered()), this, SLOT(startClicked()));
	connect(stopAction, SIGNAL(triggered()), this, SLOT(stopClicked()));

	//displayListView = new QListView();
	exitButton = createButton(tr("Exit"),SLOT(exitClicked()));
	startButton = createButton(tr("Start"), SLOT(startClicked()));
	stopButton = createButton(tr("Stop"), SLOT(stopClicked()));

	stopButton->setEnabled(false);
	stopAction->setEnabled(false);

	QGridLayout *mainLayout = new QGridLayout;

	mainLayout->setMenuBar(menuBar);
	mainLayout->addWidget(mainLabel,1,0,1,8);
	mainLayout->addWidget(fromLabel,2,0,1,2);
	mainLayout->addWidget(fromValue,2,2,1,3);
	mainLayout->addWidget(toLabel,  2,6,1,3);
	mainLayout->addWidget(toValue,  2,7,1,3);

	mainLayout->addWidget(displayListView,3,0,1,12);
	mainLayout->addWidget(progressBar,4,0,1,12);
	mainLayout->addWidget(numberOfPrimes,5,0,1,6);
	mainLayout->addWidget(startButton,6,0,1,4);
	mainLayout->addWidget(stopButton, 6,4,1,4);
	mainLayout->addWidget(exitButton, 6,8,1,4);

	//connect(signalMapper, SIGNAL(mapped(QString)), this, SIGNAL(clicked(QString)));
	setLayout(mainLayout);
	setWindowTitle(tr("Primes"));
}

QPushButton *Primes::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
	QOUT(button << "button Connect" <<endl);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}

void Primes::exitClicked()
{
	this->close();
}

void Primes::startClicked()
{

	stopButton->setEnabled(true);
	stopAction->setEnabled(true);
	progressBar->setVisible(true);
	lowerBound = fromValue->text().toULongLong();
    upperBound = toValue->text().toULongLong();
	pthread_create(&myThread, NULL, runEratosthenesSieve, NULL);
	//pthread_join(thread_tid[0], NULL);

	startButton->setEnabled(false);
	startAction->setEnabled(false);
}

void Primes::stopClicked()
{
	startButton->setEnabled(true);
	stopButton->setEnabled(false);
	startAction->setEnabled(true);
	stopAction->setEnabled(false);
	progressBar->setVisible(false);
}

