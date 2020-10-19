#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setInputValidators();

	connect(ui->edtInputFile, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->edtOutputFile, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->edtP, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->edtQ, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->edtRDecipher, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->edtSecretKeyCipher, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->edtSecretKeyDecipher, SIGNAL(textChanged(QString)), this, SLOT(checkFields()));
	connect(ui->rbtnCipher, SIGNAL(clicked()), this, SLOT(checkFields()));
	connect(ui->rbtnDecipher, SIGNAL(clicked()), this, SLOT(checkFields()));

    enableCipher(true);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setInputValidators(){
	QIntValidator *inputValidator = new QIntValidator(1, 65535, this);

	ui->edtP->setValidator(inputValidator);
	ui->edtQ->setValidator(inputValidator);
	ui->edtRDecipher->setValidator(inputValidator);
	ui->edtSecretKeyCipher->setValidator(inputValidator);
	ui->edtSecretKeyDecipher->setValidator(inputValidator);
}

void MainWindow::enableCipher(bool enabled)
{
	ui->grpCipher->setEnabled(enabled);

	if (enabled){
		enableDecipherMode(false);

	}
}

void MainWindow::enableDecipherMode(bool enabled)
{
	ui->grpDecipher->setEnabled(enabled);

	if (enabled){

        enableCipher(false);
	}
}



void MainWindow::on_rbtnCipher_clicked()
{
    enableCipher(true);
}

void MainWindow::on_rbtnDecipher_clicked()
{
	enableDecipherMode(true);
}



void MainWindow::on_btnChooseInputFile_clicked()
{
	QString inputFileName = QFileDialog::getOpenFileName(this, "Открыть файл", 0, "Все файлы (*)");
	if (!inputFileName.isNull()){
		ui->edtInputFile->setText(inputFileName);
	}
}

void MainWindow::on_btnChooseOutputFile_clicked()
{
	QString outputFileName = QFileDialog::getSaveFileName(this, "Сохранить файл", 0, "Все файлы (*)");
	if (!outputFileName.isNull()){
		ui->edtOutputFile->setText(outputFileName);
	}
}

void MainWindow::displayError(ErrorType errorType){
	QMessageBox errorMessageBox;
	errorMessageBox.setWindowTitle("Ошибка");
	errorMessageBox.setIcon(QMessageBox::Critical);

	switch(errorType){
		case E_TOO_BIG_KEY:
            errorMessageBox.setText("Ключа не должен быть больше двух байт!");
			break;
		case E_TOO_BIG_P_Q:
			errorMessageBox.setText("Произведение p и q больше двух байт!");
			break;
		case E_NOT_PRIME_P:
            errorMessageBox.setText("p простое число!");
			break;
		case E_NOT_PRIME_Q:
            errorMessageBox.setText("q простое число!");
			break;
		case E_INVALID_KEY:
            errorMessageBox.setText("Ключ не является простым со значением функции Эйлера");
			break;
		case E_INVALID_INPUT_FILE:
            errorMessageBox.setText("Ошибка чтения");
			break;
		case E_INVALID_OUTPUT_FILE:
            errorMessageBox.setText("Ошибка записи ");
			break;
		case E_TOO_SMALL_P_Q:
            errorMessageBox.setText(" p и q меньше 256!");
			break;		
		default:
            errorMessageBox.setText("");
			break;
	}
	errorMessageBox.exec();
}

void MainWindow::decipherMode(QString inputFileName, QString outputFileName){
	word secretKey = ui->edtSecretKeyDecipher->text().toUInt();
	word r = ui->edtRDecipher->text().toUInt();

	MainWindow::setEnabled(false);

    RSACrypt *rsaWorker = new RSACrypt(inputFileName, outputFileName, secretKey, r, MODE_DECIPHER);
	QThread *workerThread = getRSAWorkerThread(rsaWorker);

	workerThread->start();
	emit doWork();
}



QThread *MainWindow::getRSAWorkerThread(RSACrypt *worker)
{
	QThread *workerThread= new QThread();

	connect(this, SIGNAL(destroyed()), worker, SLOT(deleteLater()));
	connect(worker, SIGNAL(destroyed()), workerThread, SLOT(quit()));
	connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
	worker->moveToThread(workerThread);
	connect(this, SIGNAL(doWork()), worker, SLOT(startWork()));


	connect(worker, SIGNAL(done(QString, QString)), this, SLOT(workDone(QString,QString)));

	connect(worker, SIGNAL(progress(int)), ui->progressBar, SLOT(setValue(int)));

	return workerThread;
}

bool MainWindow::validCipherModeFields()
{
	bool zero = ui->edtP->text().toInt() == 0 ||
				ui->edtQ->text().toInt() == 0 ||
				ui->edtSecretKeyCipher->text().toInt() == 0;

	return	ui->edtP->text() != "" &&
			ui->edtQ->text() != "" &&
			ui->edtSecretKeyCipher->text() != "" &&
			!zero;
}

bool MainWindow::validDecipherModeFields()
{
	bool zero = ui->edtRDecipher->text().toInt() == 0 ||
				ui->edtSecretKeyDecipher->text().toInt() == 0;

	return	ui->edtRDecipher->text() != "" &&
			ui->edtSecretKeyDecipher->text() != "" &&
			!zero;
}



bool MainWindow::validFilesFields()
{
	return	ui->edtInputFile->text() != "" &&
			ui->edtOutputFile->text() != "";
}

void MainWindow::cipherMode(QString inputFileName, QString outputFileName){
	word q = ui->edtQ->text().toUInt();
	word p = ui->edtP->text().toUInt();
	uint32 r = q * p;
	word secretKey = ui->edtSecretKeyCipher->text().toUInt();

	bool error = false;

	if (r > 65535){
		displayError(E_TOO_BIG_P_Q);
		error = true;
	} else {
		if (r < 256){
			displayError(E_TOO_SMALL_P_Q);
			error = true;
		}
	}

	word eulerValue = (q - 1)*(p - 1);

	if (gcd(eulerValue, secretKey) != 1){
		displayError(E_INVALID_KEY);
		error = true;
	}

    if (!primeIsTru(p)){
		displayError(E_NOT_PRIME_P);
		error = true;
	}
    if (!primeIsTru(q)){
		displayError(E_NOT_PRIME_Q);
		error = true;
	}

	if (error){
		ui->txtLog->clear();
		return;
	}

    word openKey = multInvers(secretKey, eulerValue);

	ui->txtLog->appendPlainText("\nОткрытый ключ: e = " + QString::number(openKey) + ", r = " + QString::number(r));

	MainWindow::setEnabled(false);

    RSACrypt *rsaWorker = new RSACrypt(inputFileName, outputFileName, openKey, r, MODE_CIPHER);
	QThread *workerThread = getRSAWorkerThread(rsaWorker);

	workerThread->start();
	emit doWork();
}

void MainWindow::on_btnProcess_clicked()
{
	QString inputFileName = getInputFileName(), outputFileName = getOutputFileName();
	QFile input(inputFileName), output(outputFileName);

	if (!input.open(QIODevice::ReadOnly)){
		displayError(E_INVALID_INPUT_FILE);
		return;
	}

	if (!output.open(QIODevice::WriteOnly)){
		displayError(E_INVALID_OUTPUT_FILE);
		return;
	}

	input.close();
	output.close();

    ui->txtLog->clear();


	if (ui->rbtnCipher->isChecked()){
		cipherMode(inputFileName, outputFileName);
		return;
	}

	if (ui->rbtnDecipher->isChecked()){
		decipherMode(inputFileName, outputFileName);
		return;
	}


}

QString MainWindow::getInputFileName(){
	return ui->edtInputFile->text();
}

QString MainWindow::getOutputFileName(){
	return ui->edtOutputFile->text();
}

void MainWindow::checkFields()
{
	bool validFields = validFilesFields();



	if (ui->rbtnCipher->isChecked()){
		validFields = validFields && validCipherModeFields();

	}
	if (ui->rbtnDecipher->isChecked()){
		validFields = validFields && validDecipherModeFields();
	}

	ui->btnProcess->setEnabled(validFields);
}

void MainWindow::workDone(QString srcFile, QString resultFile)
{
    RSACrypt *rsaWorker = static_cast<RSACrypt *>(sender());
	delete rsaWorker;


    ui->txtLog->appendPlainText(srcFile);

    ui->txtLog->appendPlainText(resultFile);

	MainWindow::setEnabled(true);


    ui->progressBar->setValue(0);

}

void MainWindow::on_btnSwapFileNames_clicked()
{
	QString tmp = ui->edtInputFile->text();
	ui->edtInputFile->setText(ui->edtOutputFile->text());
	ui->edtOutputFile->setText(tmp);
}
