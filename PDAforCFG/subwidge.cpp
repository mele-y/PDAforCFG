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

void subwidge::setResult(bool flag,pdaMsg Msg){
    qDebug()<<Msg.second;
    ui->textBrowser->clear();
    if(flag){
        ui->textBrowser->append("Accept");
        QString str="祝贺你，该串"+Msg.second+"!";
        ui->textBrowser->append(str);

    }
    else{
        ui->textBrowser->append("Reject");
        QString str=QString("错误代码%1：").arg(Msg.first)+Msg.second+"!";
        ui->textBrowser->append(str);
    }
}
void subwidge::closeEvent(QCloseEvent *event){
    ui->textEdit->clear();
    ui->textBrowser->clear();
}
