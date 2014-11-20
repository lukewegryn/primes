#ifndef PRIMES_H
#define PRIMES_H
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QLineEdit>
#include <stringListModel.h>
#include <QProgressBar>
class QPushButton;
class QListView;

class Primes:public QWidget
{
	Q_OBJECT

	public:
		Primes(QWidget *parent = 0);
		//void *runEratosthenesSieve(void);
		//static void *runEratosthenesSieve_helper(void *context);
	    void emitUpdateModel(QString);

	signals:
		void updateModel(QString);

	private slots:
		//void fileClicked();
		void startClicked();
		void stopClicked();
		void exitClicked();
		void appendToModel(QString);
		
	private:
		QPushButton *createButton(const QString &text, const char *member);
		QMenuBar *menuBar;
		QMenu *fileMenu;
		QLineEdit *fromValue;
		QLineEdit *toValue;
		QListView *displayListView;
		QAction *startAction;
		QAction *stopAction;
		QAction *exitAction;
		QPushButton *startButton;
		QPushButton *stopButton;
		QPushButton *exitButton;
		StringListModel *listModel;
		QStringList primeList;
		QProgressBar *progressBar;
		pthread_t myThread;
};

#endif