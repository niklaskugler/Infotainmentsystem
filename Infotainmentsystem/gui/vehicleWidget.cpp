#include "vehicleWidget.h"
#include "ui_vehicleWidget.h"
#include <QDateTime>
#include <QTimer>
#include "infotainmentsystemWindow.h"

#include "core/global_variables.h"

VehicleWidget::VehicleWidget(InfotainmentsystemWindow *menu, QWidget *parent) :
     QWidget(parent),
    ui(new Ui::VehicleWidget)
{
    ui->setupUi(this);

    menu_obj = menu;
    infotainmentsystem_obj = menu;

    //Initialierung des timers für Uhrzeit aktualisierung
    timer_fahrzeug = new QTimer(this);
    connect(timer_fahrzeug, &QTimer::timeout, this, &VehicleWidget::set_time);
    timer_fahrzeug->start(1000);

    //Homebutton einrichten und mit Slot verbinden
    HomeButton = VehicleWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(HomeButton,&QPushButton::clicked, this, &VehicleWidget::go_home);

    //Menü Buttons finden
    fahrmodus_button = VehicleWidget::findChild<QToolButton *>("toolButton");//toolButton_2
    klima_button = VehicleWidget::findChild<QToolButton *>("toolButton_2");
    fahrerassistenz_button = VehicleWidget::findChild<QToolButton *>("toolButton_3");

    //Menü Buttons mit SLots verbinden
    QObject::connect(fahrmodus_button,&QToolButton::clicked, this, &VehicleWidget::display_fahrmodus);
    QObject::connect(klima_button,&QToolButton::clicked, this, &VehicleWidget::display_klima);
    QObject::connect(fahrerassistenz_button,&QToolButton::clicked, this, &VehicleWidget::display_fahrerassistenz);


    fahrmodus_obj = new DriveModeWidget(this);
    ui->page_driveMode->layout()->addWidget(fahrmodus_obj);
    connect(fahrmodus_obj, &DriveModeWidget::homeButtonClicked, this, &VehicleWidget::showMainMenu);

    klima_obj = new ClimateControlWidget(this);
    ui->page_climate->layout()->addWidget(klima_obj);
    connect(klima_obj, &ClimateControlWidget::homeButtonClicked, this, &VehicleWidget::showMainMenu);

    fahrerassistenz_obj = new DriveAssistWidget(this);
    ui->page_driveAssistant->layout()->addWidget(fahrerassistenz_obj);
    connect(fahrerassistenz_obj, &DriveAssistWidget::homeButtonClicked, this, &VehicleWidget::showMainMenu);

    //Side Menu PushButtons verknüpfen
    side_menu[0] = VehicleWidget::findChild<QPushButton *>("pb_Menu");
    side_menu[1] = VehicleWidget::findChild<QPushButton *>("pb_Radio");
    side_menu[2] = VehicleWidget::findChild<QPushButton *>("pb_Media");
    side_menu[3] = VehicleWidget::findChild<QPushButton *>("pb_Phone");
    side_menu[4] = VehicleWidget::findChild<QPushButton *>("pb_Navigation");

    //Side Menu Pbs mit entsprechenden Slots zum öffnen des neuen Fensters verknüpfen
    QObject::connect(side_menu[0],&QPushButton::clicked, this, &VehicleWidget::side_menu_clicked);
    QObject::connect(side_menu[1],&QPushButton::clicked, this, &VehicleWidget::side_menu_clicked);
    QObject::connect(side_menu[2],&QPushButton::clicked, this, &VehicleWidget::side_menu_clicked);
    QObject::connect(side_menu[3],&QPushButton::clicked, this, &VehicleWidget::side_menu_clicked);
    QObject::connect(side_menu[4],&QPushButton::clicked, this, &VehicleWidget::side_menu_clicked);

}

VehicleWidget::~VehicleWidget()
{
    delete ui;
    delete fahrerassistenz_obj;
    delete klima_obj;
    delete fahrmodus_obj;
    delete timer_fahrzeug;
}

void VehicleWidget::set_time()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void VehicleWidget::go_home()       //wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void VehicleWidget::display_fahrmodus()
{
    ui->stackedWidget->setCurrentWidget(ui->page_driveMode);
}

void VehicleWidget::display_klima()
{
    ui->stackedWidget->setCurrentWidget(ui->page_climate);
}

void VehicleWidget::display_fahrerassistenz()
{
    ui->stackedWidget->setCurrentWidget(ui->page_driveAssistant);
}

void VehicleWidget::side_menu_clicked()
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();
    qInfo() << button_name << " pressed";
    if(button_name == side_menu[0]->objectName())
    {
        infotainmentsystem_obj->showHomeScreen();
    }
    if(button_name == side_menu[1]->objectName())
    {
        infotainmentsystem_obj->disp_radio();
    }
    if(button_name == side_menu[2]->objectName())
    {
        infotainmentsystem_obj->disp_media();
    }
    if(button_name == side_menu[3]->objectName())
    {
        infotainmentsystem_obj->disp_phone();
    }
    if(button_name == side_menu[4]->objectName())
    {
        infotainmentsystem_obj->disp_navi();
    }
    return;
}

void VehicleWidget::showMainMenu()
{
    ui->stackedWidget->setCurrentWidget(ui->page_start);
}

void VehicleWidget::update_backround()       //Funktion um Backround der Subfenster Anzupassen
{
    klima_obj->setStyleSheet(backround_color);
    fahrmodus_obj->setStyleSheet(backround_color);
    fahrerassistenz_obj->setStyleSheet(backround_color);
}
