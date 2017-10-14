#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;
    double prevNum;

private slots: //a slot is a function that executes when a signal is emitted.
    void digit_pressed();
    void on_pushButton_dec_released();
    void unary_op_pressed();
    void operator_pressed();
    void on_pushButton_equal_released();
};

#endif // CALCULATOR_H
