#ifndef PRIMES_H
#define PRIMES_H
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QLineEdit>

class QPushButton;
class QListView;

class Primes:public QWidget
{
	Q_OBJECT

	public:
		Primes(QWidget *parent = 0);

	private slots:
		//void fileClicked();
		void startClicked();
		void stopClicked();
		void exitClicked();
		
	private:
		QPushButton *createButton(const QString &text, const char *member);
		QMenuBar *menuBar;
		QMenu *fileMenu;
		QLineEdit *fromValue;
		QLineEdit *toValue;
		void abortOperatiion();
		QListView *displayListView;
		QAction *startAction;
		QAction *stopAction;
		QAction *exitAction;
};

#endif