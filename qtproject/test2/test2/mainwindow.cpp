#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "qdebug.h"
#include "qpdfwriter.h"
#include "qpainter.h"
#include "qaxobject.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonExport_clicked()
{
    //QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Text"),"",tr("Text files(*.pdf)")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
//      QFile file(filename);
//      if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//          QMessageBox::warning(this, tr("Read File"),tr("Cannot open file:\n%1").arg(filename));
//          return;
//      }
//      else
//      {
//          QString str1, str2, qstr_similarity, sumqstr;
//          int rows = 3;
//          for(int i = 0; i < rows; ++i)
//          {
//               str1 = "aaaa";
//               str2 = "bbbbb";
//               qstr_similarity = "cccccc";
//               sumqstr = sumqstr + str1 + "\t" + str2 + "\t" + qstr_similarity + "\n";
//          }

//          QTextStream in(&file);
//          in << sumqstr;
//          qDebug() << rows << filename << "\n" << sumqstr;
//          file.close();
//      }
        QFile f(filename);
        f.open(QIODevice::WriteOnly);
        QPdfWriter* writer = new QPdfWriter(&f);
        QPainter* p = new QPainter(writer);
        writer->setPageSize(QPagedPaintDevice::A5);
        p->drawText(QRect(100, 100, 2000, 200), "test1");//第一个页面
        writer->newPage();
        p->drawText(QRect(100, 100, 2000, 200), "test2");//第二个页面
        delete p;
        delete writer;
        f.close();
    }
}

QStringList MainWindow::getCheckBoxTitle()
{
    QStringList titles;
    this->seqnums.clear();
    if (ui->checkBox1->isChecked()){
        titles << ui->checkBox1->text();
        this->seqnums<<"1";
    }
    if (ui->checkBox2->isChecked()){
        titles << ui->checkBox2->text();
        this->seqnums<<"2";
    }
    if (ui->checkBox3->isChecked()){
        titles << ui->checkBox3->text();
        this->seqnums<<"3";
    }
    if (ui->checkBox4->isChecked()){
        titles << ui->checkBox4->text();
        this->seqnums<<"4";
    }
    if (ui->checkBox5->isChecked()){
        titles << ui->checkBox5->text();
        this->seqnums<<"5";
    }
    if (ui->checkBox6->isChecked()){
        titles << ui->checkBox6->text();
        this->seqnums<<"6";
    }
    if (ui->checkBox7->isChecked()){
        titles << ui->checkBox7->text();
        this->seqnums<<"7";
    }
    if (ui->checkBox8->isChecked()){
        titles << ui->checkBox8->text();
        this->seqnums<<"8";
    }
    if (ui->checkBox9->isChecked()){
        titles << ui->checkBox9->text();
        this->seqnums<<"9";
    }
    if (ui->checkBox10->isChecked()){
        titles << ui->checkBox10->text();
        this->seqnums<<"10";
    }
    if (ui->checkBox11->isChecked()){
        titles << ui->checkBox11->text();
        this->seqnums<<"11";
    }
    if (ui->checkBox12->isChecked()){
        titles << ui->checkBox12->text();
        this->seqnums<<"12";
    }
    if (ui->checkBox13->isChecked()){
        titles << ui->checkBox13->text();
        this->seqnums<<"13";
    }
    if (ui->checkBox14->isChecked()){
        titles << ui->checkBox14->text();
        this->seqnums<<"14";
    }
    if (ui->checkBox15->isChecked()){
        titles << ui->checkBox15->text();
        this->seqnums<<"15";
    }
    if (ui->checkBox16->isChecked()){
        titles << ui->checkBox16->text();
        this->seqnums<<"16";
    }
    if (ui->checkBox17->isChecked()){
        titles << ui->checkBox17->text();
        this->seqnums<<"17";
    }
    if (ui->checkBox18->isChecked()){
        titles << ui->checkBox18->text();
        this->seqnums<<"18";
    }
    if (ui->checkBox19->isChecked()){
        titles << ui->checkBox19->text();
        this->seqnums<<"19";
    }
    if (ui->checkBox20->isChecked()){
        titles << ui->checkBox20->text();
        this->seqnums<<"20";
    }
    if (ui->checkBox21->isChecked()){
        titles << ui->checkBox21->text();
        this->seqnums<<"21";
    }
    if (ui->checkBox22->isChecked()){
        titles << ui->checkBox22->text();
        this->seqnums<<"22";
    }
    if (ui->checkBox23->isChecked()){
        titles << ui->checkBox23->text();
        this->seqnums<<"23";
    }
    if (ui->checkBox24->isChecked()){
        titles << ui->checkBox24->text();
        this->seqnums<<"24";
    }
    if (ui->checkBox25->isChecked()){
        titles << ui->checkBox25->text();
        this->seqnums<<"25";
    }
    if (ui->checkBox26->isChecked()){
        titles << ui->checkBox26->text();
        this->seqnums<<"26";
    }
    if (ui->checkBox27->isChecked()){
        titles << ui->checkBox27->text();
        this->seqnums<<"27";
    }
    if (ui->checkBox28->isChecked()){
        titles << ui->checkBox28->text();
        this->seqnums<<"28";
    }
    if (ui->checkBox29->isChecked()){
        titles << ui->checkBox29->text();
        this->seqnums<<"29";
    }
    if (ui->checkBox30->isChecked()){
        titles << ui->checkBox30->text();
        this->seqnums<<"30";
    }
    if (ui->checkBox31->isChecked()){
        titles << ui->checkBox31->text();
        this->seqnums<<"31";
    }
    if (ui->checkBox32->isChecked()){
        titles << ui->checkBox32->text();
        this->seqnums<<"32";
    }
    if (ui->checkBox33->isChecked()){
        titles << ui->checkBox33->text();
        this->seqnums<<"33";
    }
    if (ui->checkBox34->isChecked()){
        titles << ui->checkBox34->text();
        this->seqnums<<"34";
    }

    return titles;
}

void MainWindow::on_pushButtonSelect_clicked()
{
    QStringList header = this->getCheckBoxTitle();
    ui->tableWidget->setColumnCount(header.length());
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for (int i=0; i<header.length();i++){
        ui->tableWidget->setColumnWidth(i,(ui->tableWidget->width()/header.length() >100)?ui->tableWidget->width()/header.length():100);
    }

    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (constQString&)", "f:\test.xlsx");


    work_books->dynamicCall("Add(void)");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);//获取工作表集合的工作表1，即sheet1

    for (int i = 0; i < 12; i++)
    {
        int count = 100;
        for (int j = 0; j < 100; j++)
        {
            QAxObject *cellnum;
            QString num = (QChar)('A' + i) + QString::number(j + 1);
            cellnum = worksheet->querySubObject("Range(QVariant, QVariant)", num);//获取单元格
            cellnum->dynamicCall("SetValue(const QVariant&)", QVariant(i+j));
        }
    }

    workbook->dynamicCall("SaveAs(const QString&)", QString("./test.xlsx"));
    workbook->dynamicCall("Close()");//关闭工作簿
    excel.dynamicCall("Quit()");//关闭excel

}

void MainWindow::on_pushButtonUpdate_clicked()
{
    //QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "修改", "确定保存已修改内容？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
            QMessageBox::aboutQt(NULL, "About Qt");
    }
}
void MainWindow::on_pushButton_clicked(){}
void MainWindow::on_pushButton_2_clicked(){}
void MainWindow::on_pushButton_3_clicked(){}
void MainWindow::on_pushButtonSelectAll_clicked(){}
void MainWindow::on_pushButtonSelectAll_clicked(bool checked){}

void MainWindow::setAllCheckboxSelectedorNot(bool flag)
{
    ui->checkBox1->setChecked(flag);
    ui->checkBox2->setChecked(flag);
    ui->checkBox3->setChecked(flag);
    ui->checkBox4->setChecked(flag);
    ui->checkBox5->setChecked(flag);
    ui->checkBox6->setChecked(flag);
    ui->checkBox7->setChecked(flag);
    ui->checkBox8->setChecked(flag);
    ui->checkBox9->setChecked(flag);
    ui->checkBox10->setChecked(flag);
    ui->checkBox11->setChecked(flag);
    ui->checkBox12->setChecked(flag);
    ui->checkBox13->setChecked(flag);
    ui->checkBox14->setChecked(flag);
    ui->checkBox15->setChecked(flag);
    ui->checkBox16->setChecked(flag);
    ui->checkBox17->setChecked(flag);
    ui->checkBox18->setChecked(flag);
    ui->checkBox19->setChecked(flag);
    ui->checkBox20->setChecked(flag);
    ui->checkBox21->setChecked(flag);
    ui->checkBox22->setChecked(flag);
    ui->checkBox23->setChecked(flag);
    ui->checkBox24->setChecked(flag);
    ui->checkBox25->setChecked(flag);
    ui->checkBox26->setChecked(flag);
    ui->checkBox27->setChecked(flag);
    ui->checkBox28->setChecked(flag);
    ui->checkBox29->setChecked(flag);
    ui->checkBox30->setChecked(flag);
    ui->checkBox31->setChecked(flag);
    ui->checkBox32->setChecked(flag);
    ui->checkBox33->setChecked(flag);
    ui->checkBox34->setChecked(flag);
}

void MainWindow::on_pushButtonAll_clicked(bool checked)
{
    qDebug() <<"checked:"<< checked;
    if (!flag){
        setAllCheckboxSelectedorNot(!flag);
        ui->pushButtonAll->setText("取消全选");
        flag =true;
    }else{
        setAllCheckboxSelectedorNot(!flag);
        ui->pushButtonAll->setText("全    选");
        flag =false;
    }
}
