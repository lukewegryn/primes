#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include "primes.h"


int main(int argc, char ** argv) {
    QApplication app(argc, argv);

    Primes myPrimes;

    myPrimes.show();
    return app.exec();   // enters event loop
  }