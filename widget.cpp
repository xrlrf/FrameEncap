#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include "frameencap.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_PreamBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","输入数据为空!");
    }else{
        FrameEncap frame;
        QString info = QString::fromStdString(frame.getPreamble());
        ui->PreamLineEdit->setText(info);
    }
}

void Widget::on_DelimBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","输入数据为空!");
    }else{
        FrameEncap frame;
        QString info = QString::fromStdString(frame.getDelimiter());
        ui->DelimLineEdit->setText(info);
    }
}

void Widget::on_DestiBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","输入数据为空!");
    }else{
        FrameEncap frame;
        QString info = QString::fromStdString(frame.getDestination());
        ui->DestiLineEdit->setText(info);
    }
}

void Widget::on_SourceBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","输入数据为空!");
    }else{
        FrameEncap frame;
        QString info2 = QString::fromStdString(frame.getSource());
        ui->SourceLineEdit->setText(info2);
    }
}

void Widget::on_LengthBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","输入数据为空!");
    }else{
        FrameEncap frame;
        string data = info.toStdString();
        frame.SetData(data);
        frame.CheckSum();
        QString info2 = QString::fromStdString(frame.getLength());
        ui->LengthLineEdit->setText(info2);
    }
}

void Widget::on_DataBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","数据为空!");
    }else{
        FrameEncap frame;
        string data = info.toStdString();
        frame.SetData(data);
        frame.CheckSum();
        QString info2 = QString::fromStdString(frame.getData());
        ui->DataLineEdit->setText(info2);
    }
}

void Widget::on_CheckBtn_clicked()
{
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","数据为空!");
    }else{
        FrameEncap frame;
        string data = info.toStdString();
        frame.SetData(data);
        frame.CheckSum();
        QString info = QString::fromStdString(frame.getCheckNum());
        ui->CheckLineEdit->setText(info);
    }
}

void Widget::on_ShowallBtn_clicked()
{
    ui->textEdit_2->setReadOnly(true);
    QString info = ui->textEdit->toPlainText();
    if(info == 0)
    {
        QMessageBox::about(this,"Message","数据为空!");
    }else{
        FrameEncap frame;
        string data = info.toStdString();
        frame.SetData(data);
        frame.CheckSum();
        QString info = QString::fromStdString(frame.ShowAll());
        ui->textEdit_2->setText(info);
    }
}
