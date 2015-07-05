#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mathinterpreter.h"
#include <QtDebug>
#include <QSettings>

QString inputString = "";
int base = 16;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("TheArrowKeyProject");
    QCoreApplication::setOrganizationDomain("TAKP.io");
    QCoreApplication::setApplicationName("0xCA1C");

    QSettings settings;
    QString stringBase = settings.value("calc/base", "10 - dec").toString();

    ui->comboBoxBase->setCurrentText(stringBase);

    on_comboBoxBase_currentTextChanged(stringBase);

    ui->labelError->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateDisplay(){
    ui->textMainDisplay->setText(inputString);
}

void MainWindow::on_buttonNumber_clicked(int number) {
    inputString.insert(ui->textMainDisplay->cursorPosition(), QString::number(number, base).toUpper());
    updateDisplay();
}

void MainWindow::on_buttonSymbol_clicked(QChar symbol) {
    inputString.insert(ui->textMainDisplay->cursorPosition(), symbol);
    updateDisplay();
}

void MainWindow::on_buttonCalculate_clicked() {
    try{
        inputString = MathInterpreter::interpret(ui->textMainDisplay->text(), base);
        ui->labelError->setText("");
    }catch(FailedInterpret e){
        inputString = "";
        ui->labelError->setText(e.message);
    }

    updateDisplay();
}

void MainWindow::on_comboBoxBase_currentTextChanged(const QString &text) {

    on_buttonCalculate_clicked();

    QString s = text.left(2);
    bool* okay = new bool(false);
    int newBase = s.toInt(okay);
    if(*okay){
        inputString = MathInterpreter::numToQString(MathInterpreter::QStringToNum(inputString, base), newBase);
        base = newBase;

        QSettings settings;

        settings.setValue("calc/base", text);
    }else{
        ui->labelError->setText("Base out of range");
        ui->comboBoxBase->setCurrentText(QString(base));
    }
    updateDisplay();

    delete okay;

    ui->buttonNumberF->setEnabled(base > 0xF);
    ui->buttonNumberE->setEnabled(base > 0xE);
    ui->buttonNumberD->setEnabled(base > 0xD);
    ui->buttonNumberC->setEnabled(base > 0xC);
    ui->buttonNumberB->setEnabled(base > 0xB);
    ui->buttonNumberA->setEnabled(base > 0xA);
    ui->buttonNumber9->setEnabled(base > 0x9);
    ui->buttonNumber8->setEnabled(base > 0x8);
    ui->buttonNumber7->setEnabled(base > 0x7);
    ui->buttonNumber6->setEnabled(base > 0x6);
    ui->buttonNumber5->setEnabled(base > 0x5);
    ui->buttonNumber4->setEnabled(base > 0x4);
    ui->buttonNumber3->setEnabled(base > 0x3);
    ui->buttonNumber2->setEnabled(base > 0x2);
    ui->buttonNumber1->setEnabled(base > 0x1);
    ui->buttonNumber0->setEnabled(base > 0x0);


}

void MainWindow::on_textMainDisplay_textEdited(const QString &arg1) {
    inputString = arg1;
}

void MainWindow::on_buttonAllClear_clicked() {
    inputString = "";
    updateDisplay();
}
