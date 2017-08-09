#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList getCheckBoxTitle();
    void setAllCheckboxSelectedorNot(bool flag);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButtonExport_clicked();

    void on_pushButtonSelect_clicked();

    void on_pushButtonUpdate_clicked();

    void on_pushButtonSelectAll_clicked();

    void on_pushButtonSelectAll_clicked(bool checked);

    void on_pushButtonAll_clicked(bool checked);

private:
    Ui::MainWindow *ui;   
    QStringList seqnums;
    bool flag;
};

#endif // MAINWINDOW_H
