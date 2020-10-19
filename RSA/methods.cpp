#include "methods.h"

word fastExpPay(word number, word power, word modulo)
{
	word result = 1;

	while (power){
		while (!(power % 2)){
			power /= 2;
			number = ((uint32)number * number) % modulo;
		}
		power--;
		result = ((uint32)result * number) % modulo;
	}
	return result;
}

word multInvers(word number, word modulo)
{
	int x, y;
    euclid(number, modulo, &x, &y);

	return (x % modulo + modulo) % modulo;
}

word euclid(word a, int b, int *x, int *y){
	int x1, y1;
	unsigned short d;
	if (a == 0){
		*x = 0;
		*y = 1;
		return b;
	}

    d = euclid(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return d;
}

bool primeIsTru(word number)
{
	bool result = true;

	if (number == 2)
		return true;
	if (number == 1)
		return false;
	if (!(number % 2))
		return false;

	for (int i = 3; i <= (int)sqrt(number) && result; i += 2){
		result = (number % i);
	}

	return result;
}

word gcd(word a, word b)
{
	if (!a)
		return b;

	return gcd(b % a, a);
}

void writeDByte(word out, QFile *outputFile)
{
	char outByte = out & 255;
	outputFile->write(&outByte, 1);
}

void writeCiphered(word out, QFile *outputFile)
{
	char firstByte = out & 255;
	char secondByte = out >> 8;

	outputFile->write(&secondByte, 1);
	outputFile->write(&firstByte, 1);
}

word readCiphered(QFile *inputFile)
{
	word result;
	inputFile->read(((char *)&result) + 1, 1);
	inputFile->read((char *)&result, 1);
	return result;
}

word readPlaint(QFile *inputFile)
{
	char result;
	inputFile->read(&result, 1);
	return result & 255;
}

word firstDiv(word number)
{
	if (!(number % 2))
		return 2;
	for (int i = 3; i < number / 2; i += 2){
		if (!(number % i))
			return i;
	}
	return 1;
}
