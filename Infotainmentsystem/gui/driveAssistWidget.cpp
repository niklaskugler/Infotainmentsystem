#include "DriveAssistWidget.h"
#include "ui_DriveAssistWidget.h"

#include <QDateTime>
#include <QDebug>
#include <QUrl>
#include <QTimer>

DriveAssistWidget::DriveAssistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DriveAssistWidget)
{
    ui->setupUi(this);

    parent_obj = parent;

    timer_fahrmodus = new QTimer(this);
    connect(timer_fahrmodus, &QTimer::timeout, this, &DriveAssistWidget::set_time);
    timer_fahrmodus->start(1000);

    //Homebutton einrichten und mit Slot verbinden
    BackButton = DriveAssistWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(BackButton,&QPushButton::clicked, this, &DriveAssistWidget::go_back);

    //PushBUttons Lautstärke mit Finden
    sound_front[0] = DriveAssistWidget::findChild<QPushButton *>("pushButton");
    sound_front[1] = DriveAssistWidget::findChild<QPushButton *>("pushButton_2");
    sound_front[2] = DriveAssistWidget::findChild<QPushButton *>("pushButton_3");
    sound_rear[0] = DriveAssistWidget::findChild<QPushButton *>("pushButton_4");
    sound_rear[1] = DriveAssistWidget::findChild<QPushButton *>("pushButton_5");
    sound_rear[2] = DriveAssistWidget::findChild<QPushButton *>("pushButton_6");

    //Connecten der Lautstärkebuttons zu Slots
    QObject::connect(sound_front[0],&QPushButton::clicked, this, &DriveAssistWidget::front_sound_changed);
    QObject::connect(sound_front[1],&QPushButton::clicked, this, &DriveAssistWidget::front_sound_changed);
    QObject::connect(sound_front[2],&QPushButton::clicked, this, &DriveAssistWidget::front_sound_changed);
    QObject::connect(sound_rear[0],&QPushButton::clicked, this, &DriveAssistWidget::rear_sound_changed);
    QObject::connect(sound_rear[1],&QPushButton::clicked, this, &DriveAssistWidget::rear_sound_changed);
    QObject::connect(sound_rear[2],&QPushButton::clicked, this, &DriveAssistWidget::rear_sound_changed);

    //Standardmäßig ausgewählte Buttons aktivieren
    sound_front[1]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    sound_rear[1]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");


    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/switch1.qml")));
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->show();

    ui->quickWidget_2->setSource(QUrl(QStringLiteral("qrc:/qml/switch1.qml")));
    ui->quickWidget_2->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_2->setClearColor(Qt::transparent);
    ui->quickWidget_2->show();

    ui->quickWidget_3->setSource(QUrl(QStringLiteral("qrc:/qml/switch1.qml")));
    ui->quickWidget_3->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_3->setClearColor(Qt::transparent);
    ui->quickWidget_3->show();

    ui->quickWidget_4->setSource(QUrl(QStringLiteral("qrc:/qml/switch1.qml")));
    ui->quickWidget_4->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_4->setClearColor(Qt::transparent);
    ui->quickWidget_4->show();
}

DriveAssistWidget::~DriveAssistWidget()
{
    delete ui;
    delete timer_fahrmodus;
}

void DriveAssistWidget::set_time()      //uhrzeit setzten
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void DriveAssistWidget::go_back()       //wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void DriveAssistWidget::front_sound_changed()
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();

    for(int i = 0; i < 3; i++)
    {
        if(button_name == sound_front[i]->objectName())
        {
            sound_front[i]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
            sound_front[(i+1)%3]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
            sound_front[(i+2)%3]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
        }
    }
}

void DriveAssistWidget::rear_sound_changed()
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();

    for(int i = 0; i < 3; i++)
    {
        if(button_name == sound_rear[i]->objectName())
        {
            sound_rear[i]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
            sound_rear[(i+1)%3]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
            sound_rear[(i+2)%3]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
        }
    }
}
