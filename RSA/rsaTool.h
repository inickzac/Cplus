#ifndef RSAWORKER_H
#define RSAWORKER_H

#include <QObject>
#include <QFile>

#include "types.h"
#include "methods.h"



class RSACrypt : public QObject
{
	Q_OBJECT
public:
    explicit RSACrypt(QString inputFileName, QString outputFileName, word key, word r, WorkerMode workerMode, QObject *parent = 0);

private:
	word key, r;
	QString inputFileName, outputFileName;
	WorkerMode workerMode;

signals:
	void progress(int progressValue);
	void done(QString srcFile, QString resultFile);

public slots:
	void startWork();

};

#endif
