#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNoepsilon,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
          ui->displaytext->append("消除epsilon产生式：");
         QVector<Production>p=analyzer.getUse_products();
         for(auto i :p){
             QString s=QString(i.left)+"->"+i.right;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionNounit,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
         ui->displaytext->append("消除单一产生式：");
         QVector<Production>p=analyzer.getNOsingle_products();
         for(auto i :p){
             QString s=QString(i.left)+"->"+i.right;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actionNouse,&QAction::triggered,
            [=](){
        ui->displaytext->clear();
        ui->displaytext->append("消除无用产生式：");
         QVector<Production>p=analyzer.getUse_products();
         for(auto i :p){
             QString s=QString(i.left)+"->"+i.right;
             ui->displaytext->append(s);
         }
    });

    connect(ui->actiontoG1,&QAction::triggered,
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

    connect(ui->actiontoG2,&QAction::triggered,
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

    connect(ui->actiontoG3,&QAction::triggered,
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

    connect(ui->action_PDA,&QAction::triggered,
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




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_translateButton_clicked()
{
    QTextDocument* doc =ui->GrammerTextEdit->document();
    analyzer.readGrammer(doc);
    ui->displaytext->clear();
    ui->displaytext->append("文法转换成功！");
    ui->displaytext->append("请在菜单里选择需要查看的内容！");

}

void MainWindow::on_judjeButton_clicked()
{
    QString str=ui->stringEdit->text();
    //analyzer.pda.initialPDA(analyzer.gnf.returnTset(),analyzer.gnf.returnGNFpro());
    if(analyzer.pda.inference(str)){
     ui->judgeTxt->setText("(｡>∀<｡) Accept (｡>∀<｡)");
    }
    else
     ui->judgeTxt->setText("(。•́︿•̀。) Reject (。•́︿•̀。)");
}
