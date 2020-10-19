#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QMessageBox>
#include <QFile>

#include "types.h"
#include "rsaTool.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_rbtnCipher_clicked();

	void on_rbtnDecipher_clicked();

	void on_btnChooseInputFile_clicked();

	void on_btnChooseOutputFile_clicked();

	void on_btnProcess_clicked();

	void checkFields();

	void workDone(QString srcFile, QString resultFile);

	void on_btnSwapFileNames_clicked();

signals:
	void doWork();

private:
	Ui::MainWindow *ui;

    void enableCipher(bool enabled);
	void enableDecipherMode(bool enabled);

	QString getInputFileName();
	QString getOutputFileName();

	void displayError(ErrorType errorType);

	void setInputValidators();

	void cipherMode(QString inputFileName, QString outputFileName);
	void decipherMode(QString inputFileName, QString outputFileName);

	QThread *getRSAWorkerThread(RSACrypt *worker);

	bool validCipherModeFields();
	bool validDecipherModeFields();
	bool validFilesFields();
};

#endif
