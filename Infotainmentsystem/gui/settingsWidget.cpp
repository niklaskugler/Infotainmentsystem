#include "settingsWidget.h"
#include "ui_settingsWidget.h"

#include "infotainmentsystemWindow.h"

#include <QDateTime>
#include <QTimer>

#include "core/global_variables.h"

SettingsWidget::SettingsWidget(InfotainmentsystemWindow *menu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    menu_obj = menu;
    infotainmentsystem_obj = menu;

    logic_class = new Settings();

    //Initialierung des timers für Uhrzeit aktualisierung
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SettingsWidget::set_time);
    timer->start(1000);

    //Homebutton einrichten und mit Slot verbinden
    HomeButton = SettingsWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(HomeButton,&QPushButton::clicked, this, &SettingsWidget::go_home);

    //Side Menu PushButtons in array einlesen
    side_menu[0] = SettingsWidget::findChild<QPushButton *>("pb_Menu");
    side_menu[1] = SettingsWidget::findChild<QPushButton *>("pb_Radio");
    side_menu[2] = SettingsWidget::findChild<QPushButton *>("pb_Media");
    side_menu[3] = SettingsWidget::findChild<QPushButton *>("pb_Phone");
    side_menu[4] = SettingsWidget::findChild<QPushButton *>("pb_Navigation");

    //Side Menu Pbs mit entsprechenden Slots zum öffnen des neuen Fensters verknüpfen
    QObject::connect(side_menu[0],&QPushButton::clicked, this, &SettingsWidget::side_menu_clicked);
    QObject::connect(side_menu[1],&QPushButton::clicked, this, &SettingsWidget::side_menu_clicked);
    QObject::connect(side_menu[2],&QPushButton::clicked, this, &SettingsWidget::side_menu_clicked);
    QObject::connect(side_menu[3],&QPushButton::clicked, this, &SettingsWidget::side_menu_clicked);
    QObject::connect(side_menu[4],&QPushButton::clicked, this, &SettingsWidget::side_menu_clicked);

    //Farbauswahl PushButtons in array einlesen
    color_selection[0] = SettingsWidget::findChild<QPushButton *>("pb_black_fade");
    color_selection[1] = SettingsWidget::findChild<QPushButton *>("pb_blue_fade");
    color_selection[2] = SettingsWidget::findChild<QPushButton *>("pb_black");
    color_selection[3] = SettingsWidget::findChild<QPushButton *>("pb_green_fade");
    color_selection[4] = SettingsWidget::findChild<QPushButton *>("pb_grey_fade");
    color_selection[5] = SettingsWidget::findChild<QPushButton *>("pb_red_fade");

    //Farbauswahl Pbs mit Slot zum Ändern der Farbe auswählen
    QObject::connect(color_selection[0],&QPushButton::clicked, this, &SettingsWidget::backround_selected);
    QObject::connect(color_selection[1],&QPushButton::clicked, this, &SettingsWidget::backround_selected);
    QObject::connect(color_selection[2],&QPushButton::clicked, this, &SettingsWidget::backround_selected);
    QObject::connect(color_selection[3],&QPushButton::clicked, this, &SettingsWidget::backround_selected);
    QObject::connect(color_selection[4],&QPushButton::clicked, this, &SettingsWidget::backround_selected);
    QObject::connect(color_selection[5],&QPushButton::clicked, this, &SettingsWidget::backround_selected);

    color_selection[0]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
    delete timer;
    delete logic_class;
}

void SettingsWidget::set_time()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void SettingsWidget::go_home()       //Slot: wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void SettingsWidget::side_menu_clicked()     //Slot: wird beim betätigen eines Side Menu Buttons ausgelöst
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

void SettingsWidget::backround_selected()        //Slot: Wird ausgelößt, wenn einer der Backround Buttons angeklickt wird
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();

    QString prev_backround = backround_color;

    for(int i = 0; i <6; i++)   //Prüfen, welcher Button aktiviert wurde
    {
        color_selection[i]->setStyleSheet("background-color: rgb(255, 255, 255);");
        if(color_selection[i]->objectName() == button_name)
        {
            color_selection[i]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");

            logic_class->update_color(i);
        }
    }
    if(prev_backround != backround_color)
    {
        infotainmentsystem_obj->update_backround();
    }

}
