#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void on_buttonNumber_clicked(int number);
    void on_buttonSymbol_clicked(QChar symbol);
    void updateDisplay();

private slots:

    void on_buttonNumber0_clicked(){on_buttonNumber_clicked(0x0);}
    void on_buttonNumber1_clicked(){on_buttonNumber_clicked(0x1);}
    void on_buttonNumber2_clicked(){on_buttonNumber_clicked(0x2);}
    void on_buttonNumber3_clicked(){on_buttonNumber_clicked(0x3);}
    void on_buttonNumber4_clicked(){on_buttonNumber_clicked(0x4);}
    void on_buttonNumber5_clicked(){on_buttonNumber_clicked(0x5);}
    void on_buttonNumber6_clicked(){on_buttonNumber_clicked(0x6);}
    void on_buttonNumber7_clicked(){on_buttonNumber_clicked(0x7);}
    void on_buttonNumber8_clicked(){on_buttonNumber_clicked(0x8);}
    void on_buttonNumber9_clicked(){on_buttonNumber_clicked(0x9);}
    void on_buttonNumberA_clicked(){on_buttonNumber_clicked(0xA);}
    void on_buttonNumberB_clicked(){on_buttonNumber_clicked(0xB);}
    void on_buttonNumberC_clicked(){on_buttonNumber_clicked(0xC);}
    void on_buttonNumberD_clicked(){on_buttonNumber_clicked(0xD);}
    void on_buttonNumberE_clicked(){on_buttonNumber_clicked(0xE);}
    void on_buttonNumberF_clicked(){on_buttonNumber_clicked(0xF);}

    void on_textMainDisplay_returnPressed(){on_buttonCalculate_clicked();}
    void on_buttonCalculate_clicked();

    void on_comboBoxBase_currentTextChanged(const QString &arg1);

    void on_buttonDecimal_clicked(){on_buttonSymbol_clicked('.');}

    void on_buttonParenthesisOpen_clicked(){on_buttonSymbol_clicked('(');}
    void on_buttonParenthesisClose_clicked(){on_buttonSymbol_clicked(')');}

    void on_buttonAdd_clicked(){on_buttonSymbol_clicked('+');}
    void on_buttonSubtract_clicked(){on_buttonSymbol_clicked('-');}
    void on_buttonMultiply_clicked(){on_buttonSymbol_clicked('*');}
    void on_buttonDivide_clicked(){on_buttonSymbol_clicked('/');}
    void on_buttonPower_clicked(){on_buttonSymbol_clicked('^');}

    void on_buttonOr_clicked(){on_buttonSymbol_clicked('|');}
    void on_buttonAnd_clicked(){on_buttonSymbol_clicked('&');}
    void on_buttonXor_clicked(){on_buttonSymbol_clicked(0x22BB);}
    void on_buttonShiftLeft_clicked(){on_buttonSymbol_clicked(0x00AB);}
    void on_buttonShiftRight_clicked(){on_buttonSymbol_clicked(0x00BB);}

    void on_textMainDisplay_textEdited(const QString &arg1);

    void on_buttonAllClear_clicked();

    void on_buttonFraction_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
