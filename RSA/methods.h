#ifndef RSAROUTINES
#define RSAROUTINES

#include "types.h"

#include <math.h>
#include <QFile>

word fastExpPay(word number, word power, word modulo);
word euclid(word a, int b, int *x, int *y);
word multInvers(word number, word modulo);
bool primeIsTru(word number);
word gcd(word a, word b);

word firstDiv(word number);

void writeDByte(word out, QFile *outputFile);
void writeCiphered(word out, QFile *outputFile);

word readCiphered(QFile *inputFile);
word readPlaint(QFile *inputFile);

#endif

