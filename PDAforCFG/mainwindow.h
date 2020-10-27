#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<GrammerAnalyzer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_translateButton_clicked();

    void on_judjeButton_clicked();

private:
    Ui::MainWindow *ui;
    GrammerAnalyzer analyzer;
};
#endif // MAINWINDOW_H
