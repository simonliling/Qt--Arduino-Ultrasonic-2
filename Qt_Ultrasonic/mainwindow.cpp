#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino = new QSerialPort;
    port_name = "";
    ada_arduino = false;
    serialbuffer = "";

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
       if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
           if(serialPortInfo.vendorIdentifier() == vendor_id){
               if(serialPortInfo.productIdentifier() == produk_id){
                   port_name = serialPortInfo.portName();
                   ada_arduino = true;
               }
           }
       }
    }
    if(ada_arduino){
        arduino->setPortName(port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(BacaSerial()));
    }else{
        QMessageBox::warning(this, "Error", "Arduino tidak terkoneksi");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if(arduino->isOpen()){
        arduino->close();
    }
}

//fungsi membaca serialdata
void MainWindow::BacaSerial(){
    QStringList splitdata = serialbuffer.split(", ");
    if(splitdata.length() < 3){
        dataserial = arduino->readAll();
        serialbuffer += QString::fromStdString(dataserial.toStdString());
    }else{
        serialbuffer = "";

        QStringList datasensor = serialbuffer2.split("data1:");
        if(datasensor.length() < 3){
            serialbuffer2 += QString::fromStdString(splitdata[0].toStdString());
        }else{
            serialbuffer2="";
            MainWindow::UpdateDataSensor(datasensor[1]);
        }


        QStringList dataled = serialbuffer3.split("data2:");
        if(dataled.length() < 3){
            serialbuffer3 += QString::fromStdString(splitdata[1].toStdString());
        }else{
            serialbuffer3="";
            MainWindow::UpdateDataLed(dataled[1]);
        }

    }
}

void MainWindow::UpdateDataSensor(const QString data){
    ui->lbcount->setText(data + " cm");
}

void MainWindow::UpdateDataLed(const QString data){
    if(data == "1"){
        ui->lbstatus->setText("ON");
    }else{
        ui->lbstatus->setText("OFF");
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(arduino->isWritable()){
        arduino->write("0");
    }
}
