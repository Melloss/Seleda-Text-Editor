#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Seleda");
    ui->lineNumber->setPlainText(QString::number(1));

    //Exit Action Trigerred
    connect(ui->actionExit,&QAction::triggered,[=](){
        QMainWindow::close();
    });

    //Open Button Triggered
    connect(ui->actionOpen,&QAction::triggered,[=](){
        QString filePath=QFileDialog::getOpenFileName(this,tr("Open File"),"~/Documents/",tr("Text Files(*.txt *.html *.css *.php *.js)"));
        qDebug()<<filePath;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
int prev;
bool isone=false;
void MainWindow::on_TextBoard_blockCountChanged(int newBlockCount)
{
    if(newBlockCount==1){

        ui->lineNumber->setPlainText(QString::number(1));
        ui->lineNumber->clear();
        isone=true;
    }
    if(prev>=newBlockCount){
        //Moving cursor
        QTextCursor cursor = ui->lineNumber->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,newBlockCount);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.deleteChar();
        ui->lineNumber->setTextCursor(cursor);

    }
    else{
        ui->lineNumber->appendPlainText(QString::number(newBlockCount));
        prev=newBlockCount-1;
    }
    if(isone){
        ui->lineNumber->appendPlainText(QString::number(1));
        prev=newBlockCount-1;
        isone=false;
    }

}

