
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    ui->setupUi(this);
    connect(ui->actionopen,&QAction::triggered,
            [=](){
        QString path =QFileDialog::getOpenFileName(this,"open","../");
        if(path.isEmpty()==false){
            QFile file(path);
            bool openFlag=file.open(QIODevice::ReadOnly);
            if(openFlag==true){
    #if 0
               QByteArray array=file.readAll();
               ui->GrammerTextEdit->setPlainText(array);
    #endif
               QByteArray array;
               while(file.atEnd()==false){
                   array+=file.readLine();
               }
                ui->GrammerTextEdit->setPlainText(array);
            }
            file.close();
        }


    }


            );

    connect(ui->actionsave,&QAction::triggered,
            [=](){

        QString path =QFileDialog::getSaveFileName(this,"save","../");
         if(path.isEmpty()==false){
             QFile file(path);
             bool saveFlag=file.open(QIODevice::WriteOnly);
             if(saveFlag==true){
                 QString str="待完成";
                 file.write(str.toUtf8());
             }
             file.close();
         }
    }
            );




    connect(ui->actionepsilon,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
          ui->displaytext->append("消除epsilon产生式：");
         QVector<Production>p=analyzer.getUse_products();
         for(auto i :p){
             QString s=QString(i.left)+"->"+i.right;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionunit,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
         ui->displaytext->append("消除单一产生式：");
         QVector<Production>p=analyzer.getNOsingle_products();
         for(auto i :p){
             QString s=QString(i.left)+"->"+i.right;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionuse,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
        ui->displaytext->append("消除无用产生式：");
         QVector<Production>p=analyzer.getUse_products();
         for(auto i :p){
             QString s=QString(i.left)+"->"+i.right;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionG1,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
         ui->displaytext->append("转换成G1文法：");
         QVector<GNFProduction>p=analyzer.gnf.getgnf_pro();
         for(auto i :p){
             QString t="";
             for(auto j:i.right){
                 t+=j;
             }
             QString s=QString(i.left)+"->"+t;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionG2,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
         ui->displaytext->append("转换成G2文法：");
         QVector<GNFProduction>p=analyzer.gnf.getgnf_g2();
         for(auto i :p){
             QString t="";
             for(auto j:i.right){
                 t+=j;
             }
             QString s=QString(i.left)+"->"+t;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionG3,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
        ui->displaytext->append("转换成G3文法：");
         QVector<GNFProduction>p=analyzer.gnf.getgnf_g3();
         for(auto i :p){
             QString t="";
             for(auto j:i.right){
                 t+=j;
             }
             QString s=QString(i.left)+"->"+t;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionpda,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
        ui->displaytext->append("PDA转移函数：");
         QMap<current_input,QSet<QVector<QString>>> rule=analyzer.pda.getrule();
         for(auto i:rule.keys())
         {  for(auto j:rule[i])
             {
                 QString temp;
              for(auto k:j)
              {
                 temp+=k;
              }
              QString s="(q0,"+i.input_ch+","+i.stack_ch+")=(q0,"+temp+")";
              ui->displaytext->append(s);
             }
         }
    });

    connect(ui->actioninput,&QAction::triggered,
            [=](){
        sub.show();
    }


            );

    void (subwidge::*SingalFun)(QString)=&subwidge::MySingal;
    connect(&sub,SingalFun,this,&MainWindow::DealSingal);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_translateButton_clicked()
{
    QTextDocument* doc =ui->GrammerTextEdit->document();
    GrammerAnalyzer temp;
    temp.readGrammer(doc);
    analyzer=temp;
    ui->displaytext->clear();
    ui->displaytext->append("文法转换成功！");
    ui->displaytext->append("请在菜单里选择需要查看的内容！");

}

void MainWindow::DealSingal(QString str){

    sub.setResult(analyzer.pda.inference(str));
}
