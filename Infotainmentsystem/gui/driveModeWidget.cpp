#include "driveModeWidget.h"
#include "ui_driveModeWidget.h"
#include <QDateTime>
#include <QTimer>

DriveModeWidget::DriveModeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriveModeWidget)
{
    ui->setupUi(this);

    parent_obj = parent;

    timer_fahrmodus = new QTimer(this);
    connect(timer_fahrmodus, &QTimer::timeout, this, &DriveModeWidget::set_time);
    timer_fahrmodus->start(1000);

    //Homebutton einrichten und mit Slot verbinden
    BackButton = DriveModeWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(BackButton,&QPushButton::clicked, this, &DriveModeWidget::go_back);

    //Fahrmodusauswahl mit PusButtonPointern befüllen
    drivemode_buttons[0] = DriveModeWidget::findChild<QPushButton *>("pushButton");
    drivemode_buttons[1] = DriveModeWidget::findChild<QPushButton *>("pushButton_2");
    drivemode_buttons[2] = DriveModeWidget::findChild<QPushButton *>("pushButton_3");
    drivemode_buttons[3] = DriveModeWidget::findChild<QPushButton *>("pushButton_4");

    //zu entsprechenden slots connecten
    QObject::connect(drivemode_buttons[0],&QPushButton::clicked, this, &DriveModeWidget::efficiency_mode);
    QObject::connect(drivemode_buttons[1],&QPushButton::clicked, this, &DriveModeWidget::comfort_mode);
    QObject::connect(drivemode_buttons[2],&QPushButton::clicked, this, &DriveModeWidget::auto_mode);
    QObject::connect(drivemode_buttons[3],&QPushButton::clicked, this, &DriveModeWidget::dynamic_mode);

    //QT Quickwidget (QML) einrichten (3D Modell Fahrzeug)
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/car_model.qml")));
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->show();

}

DriveModeWidget::~DriveModeWidget()
{
    delete ui;
    delete timer_fahrmodus;
}

void DriveModeWidget::set_time()      //uhrzeit setzten
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void DriveModeWidget::go_back()       //wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void DriveModeWidget::efficiency_mode()
{
    if(efficiency_status == 0)
    {
        deactivate_all();
        efficiency_status = 1;
        drivemode_buttons[0]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    }
    else
    {
        deactivate_all();
    }

    return;
}
void DriveModeWidget::comfort_mode()
{
    if(comfort_status == 0)
    {
        deactivate_all();
        comfort_status = 1;
        drivemode_buttons[1]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    }
    else
    {
        deactivate_all();
    }

    return;
}
void DriveModeWidget::auto_mode()
{
    if(auto_status == 0)
    {
        deactivate_all();
        auto_status = 1;
        drivemode_buttons[2]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    }
    else
    {
        deactivate_all();
    }

    return;
}
void DriveModeWidget::dynamic_mode()
{
    if(dynamic_status == 0)
    {
        deactivate_all();
        dynamic_status = 1;
        drivemode_buttons[3]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    }
    else
    {
        deactivate_all();
    }

    return;
}

void DriveModeWidget::deactivate_all()
{
    efficiency_status = 0;
    comfort_status = 0;
    auto_status = 0;
    dynamic_status = 0;

    for(int i = 0; i < 4; i++)
    {
        drivemode_buttons[i] -> setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
    }
}

//on: setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");

//off: setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
