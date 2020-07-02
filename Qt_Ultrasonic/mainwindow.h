#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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
    void BacaSerial();
    void UpdateDataSensor(const QString);
    void on_pushButton_clicked();    
    void UpdateDataLed(const QString);
private:
    Ui::MainWindow *ui;

    QSerialPort *arduino;
    static const quint16 vendor_id = 9025;
    static const quint16 produk_id = 67;
    QString port_name;
    bool ada_arduino;
    QByteArray dataserial;
    QString serialbuffer;
    QString serialbuffer2;
    QString serialbuffer3;
    QString serialbuffer4;
};
#endif // MAINWINDOW_H
