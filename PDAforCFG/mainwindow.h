#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<GrammerAnalyzer.h>
#include"subwidge.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DealSingal(QString str);

private slots:
    void on_translateButton_clicked();

private:
    Ui::MainWindow *ui;
    GrammerAnalyzer analyzer;
    subwidge sub;
};
#endif // MAINWINDOW_H
