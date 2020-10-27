#include "subwidge.h"
#include "ui_subwidge.h"

subwidge::subwidge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subwidge)
{
    ui->setupUi(this);
    this->setWindowTitle("推断字符串");
}

subwidge::~subwidge()
{
    delete ui;
}

void subwidge::on_pushButton_clicked()
{
   emit MySingal(ui->textEdit->toPlainText());
}

void subwidge::setResult(bool flag){
    ui->textBrowser->clear();
    if(flag)
        ui->textBrowser->append("Accept");
    else
        ui->textBrowser->append("Reject");
}
