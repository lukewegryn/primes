#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "primes.h"

int main(int argc, char ** argv) {
    QApplication app(argc, argv);
    //QWidget window;
    //window.resize(320, 240);
    Primes myPrimes;
    //myPrimes.resize(420, 520);
    //window.show();        // returns immediately
    //QPushButton *button = new QPushButton(QApplication::translate("ChildWidget", "Press me"), &window);
    //button->move(100, 100);
    //button->show();
    myPrimes.show();
    return app.exec();   // enters event loop
  }