#include "calculator.h"
#include "ui_mainwindow.h"
#include <QDebug> //for testing
#include <limits>

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    //digits
    connect(ui->pushButton_zero, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_one, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_two, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_three, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_four, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_five, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_six, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_seven, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_eight, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_nine, SIGNAL(released()), this, SLOT(digit_pressed()));

    //other ops
    connect(ui->pushButton_posneg, SIGNAL(released()), this, SLOT(unary_op_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_op_pressed()));
    connect(ui->pushButton_clear, SIGNAL(released()), this, SLOT(unary_op_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->pushButton_mul, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->pushButton_div, SIGNAL(released()), this, SLOT(operator_pressed()));

    //equal and decimal connections are done behind the scenes



    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mul->setCheckable(true);
    ui->pushButton_div->setCheckable(true);




}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::digit_pressed(){
    QPushButton* button = (QPushButton*) sender(); //returns a pointer to qObject, in this case a pushButton;
    double labelNumber;
    QString newLabel;
    labelNumber = ((ui->label->text() + button->text()).toDouble());
    if(labelNumber >= std::numeric_limits<double>::max()){
        labelNumber = 0.0;
    }
    newLabel = QString::number(labelNumber, 'g', 15);
    ui->label->setText(newLabel);
}



void Calculator::on_pushButton_dec_released()
{
    if(ui->label->text().contains(".")){
        return;
    }
    ui->label->setText(ui->label->text() + ".");
}

void Calculator::unary_op_pressed(){
   QPushButton* button = (QPushButton*) sender();
    if(button->text() == "+/-"){
        double num = (ui->label->text()).toDouble();
         num *= -1;
         ui->label->setText(QString::number(num, 'g', 15));
        qDebug() << ui->label->text();
    } else if(button->text() == "%") {
        double num = ui->label->text().toDouble() * .01;
        ui->label->setText(QString::number(num, 'g', 15));
    } else {
        double num = ui->label->text().toDouble() * 0;
        ui->label->setText(QString::number(num, 'g', 15));
    }
}

void Calculator::on_pushButton_equal_released()
{
    double labelNumber, nextNum;
    nextNum = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
       labelNumber = prevNum + nextNum;
       ui->label->setText(QString::number(labelNumber, 'g', 15));
       ui->pushButton_plus->setChecked(false);
    } else if(ui->pushButton_minus->isChecked()){
       labelNumber = prevNum - nextNum;
       ui->label->setText(QString::number(labelNumber, 'g', 15));
       ui->pushButton_minus->setChecked(false);
    } else if(ui->pushButton_div->isChecked()){
       labelNumber = prevNum / nextNum;
       ui->label->setText(QString::number(labelNumber, 'g', 15));
       ui->pushButton_div->setChecked(false);
    } else if(ui->pushButton_mul->isChecked()){
        labelNumber = prevNum * nextNum;
        ui->label->setText(QString::number(labelNumber, 'g', 15));
        ui->pushButton_mul->setChecked(false);
    }
}

void Calculator::operator_pressed(){
    QPushButton* button = (QPushButton*) sender();
    prevNum = (ui->label->text()).toDouble();//get whatever button is pressed
    button->setChecked(true); //and set it to true
    double num = ui->label->text().toDouble() * 0;
    ui->label->setText(QString::number(num, 'g', 15));
}
