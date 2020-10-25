#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GrammerAnalyzer.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_translateButton_clicked()
{
    QTextDocument* doc =ui->GrammerTextEdit->document();
    GrammerAnalyzer analyzer;
    analyzer.readGrammer(doc);
}
