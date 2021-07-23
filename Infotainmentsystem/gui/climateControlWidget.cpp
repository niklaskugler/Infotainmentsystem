#include "climateControlWidget.h"
#include "ui_climateControlWidget.h"

#include <QDateTime>
#include <QQuickItem>
#include <QTimer>

#include "core/climateControl.h"

ClimateControlWidget::ClimateControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClimateControlWidget)
{
    ui->setupUi(this);

    parent_obj = parent;

    klima_logic_class = new ClimateControl();

    /*
    hintergrund	border

    ___________rot:_________

    "#4d730404"	"#730404"	dunkel
    "#4d870505"	"#870505"
    "#4da80707"	"#a80707"
    "#4def0b0b"	"#ef0b0b"
    "#4df63c3c"	"#f63c3c"	hell

    __________grau:_________
    "#4d484848"	"#b3b3b3"	hell
    "#4d484848"	"#484848"	mittel
    "#4d404040"	"#404040"	dunkel

    __________blau:_________
    "#4d74aefa"	"#74aefa"	hell
    "#4d2781f6"	"#2781f6"
    "#4d0a5dcb"	"#0a5dcb"
    "#4d0512b6"	"#0512b6"
    "#4d0c0270"	"#0c0270"	dunkel
    */

    //initialisierung colorarray für display
    color_arr[0] = "#4d0c0270";              //dunkelblau
    color_arr[1] = "#4d0512b6";              //dunkelblau
    color_arr[2] = "#4d0a5dcb";              //blau
    color_arr[3] = "#4d2781f6";              //hellblau
    color_arr[4] = "#4d74aefa";              //hellblau
    color_arr[5] = "#4d404040";              //dunkelgrau
    color_arr[6] = "#4d484848";              //grau
    color_arr[7] = "#4db3b3b3";              //hellgrau
    color_arr[8] = "#4df63c3c";              //hellrot
    color_arr[9] = "#4def0b0b";               //hellrot
    color_arr[10] = "#4da80707";             //rot
    color_arr[11] =  "#4d870505";            //dunkelrot
    color_arr[12] =  "#4d730404";            //dunkelrot

    color_border_arr[0] = "#0c0270";              //dunkelblau
    color_border_arr[1] = "#0512b6";              //dunkelblau
    color_border_arr[2] = "#0a5dcb";              //blau
    color_border_arr[3] = "#2781f6";              //hellblau
    color_border_arr[4] = "#74aefa";              //hellblau
    color_border_arr[5] = "#404040";              //dunkelgrau
    color_border_arr[6] = "#484848";              //grau
    color_border_arr[7] = "#b3b3b3";              //hellgrau
    color_border_arr[8] = "#f63c3c";              //hellrot
    color_border_arr[9] = "#ef0b0b";               //hellrot
    color_border_arr[10] = "#a80707";             //rot
    color_border_arr[11] =  "#870505";            //dunkelrot
    color_border_arr[12] =  "#730404";            //dunkelrot


    //Initialierung des timers für Uhrzeit aktualisierung
    timer_klima = new QTimer(this);
    connect(timer_klima, &QTimer::timeout, this, &ClimateControlWidget::set_time);
    timer_klima->start(1000);

    //Homebutton einrichten und mit Slot verbinden
    BackButton = ClimateControlWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(BackButton,&QPushButton::clicked, this, &ClimateControlWidget::go_back);

    //Push Buttons finden
    off_button = ClimateControlWidget::findChild<QPushButton *>("pushButton");
    auto_button = ClimateControlWidget::findChild<QPushButton *>("pushButton_2");
    window_heater_button = ClimateControlWidget::findChild<QPushButton *>("pushButton_3");
    seat_heater_button = ClimateControlWidget::findChild<QPushButton *>("pushButton_4");
    ac_button = ClimateControlWidget::findChild<QPushButton *>("pushButton_5");

    //zu entsprechenden slots connecten
    QObject::connect(off_button,&QPushButton::clicked, this, &ClimateControlWidget::off_button_pressed);
    QObject::connect(auto_button,&QPushButton::clicked, this, &ClimateControlWidget::auto_button_pressed);
    QObject::connect(window_heater_button,&QPushButton::clicked, this, &ClimateControlWidget::window_heater_button_pressed);
    QObject::connect(seat_heater_button,&QPushButton::clicked, this, &ClimateControlWidget::seat_heater_button_pressed);
    QObject::connect(ac_button,&QPushButton::clicked, this, &ClimateControlWidget::ac_button_pressed);


    //QT Quickwidgets (QML) einrichten (Lufttemepraturanzeige Fahrer & Beifahrer)
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/klima_disp_driver.qml")));
    ui->quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget->setClearColor(Qt::transparent);
    ui->quickWidget->show();

    ui->quickWidget_2->setSource(QUrl(QStringLiteral("qrc:/qml/klima_disp_codriver.qml")));
    ui->quickWidget_2->setAttribute(Qt::WA_AlwaysStackOnTop);
    ui->quickWidget_2->setClearColor(Qt::transparent);
    ui->quickWidget_2->show();


    //Arrow Button Array mit PusButtonPointern befüllen
    arrow_buttons[0] = ClimateControlWidget::findChild<QPushButton *>("arr_up_1");
    arrow_buttons[1] = ClimateControlWidget::findChild<QPushButton *>("arr_down_1");
    arrow_buttons[2] = ClimateControlWidget::findChild<QPushButton *>("arr_up_2");
    arrow_buttons[3] = ClimateControlWidget::findChild<QPushButton *>("arr_down_2");

    //zu entsprechenden slots connecten
    QObject::connect(arrow_buttons[0],&QPushButton::clicked, this, &ClimateControlWidget::driver_increase_temp);
    QObject::connect(arrow_buttons[1],&QPushButton::clicked, this, &ClimateControlWidget::driver_decrease_temp);
    QObject::connect(arrow_buttons[2],&QPushButton::clicked, this, &ClimateControlWidget::codriver_increase_temp);
    QObject::connect(arrow_buttons[3],&QPushButton::clicked, this, &ClimateControlWidget::codriver_decrease_temp);

    //QML Code mit C++ Code verbinden (über Signal slot mechanismus) - zum ändern der farbe + temperwert des displays
    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(change_driver_temp(QVariant,QVariant,QVariant)), obj, SLOT(change_driver_temp(QVariant,QVariant,QVariant)));
    obj = ui->quickWidget_2->rootObject();
    connect(this, SIGNAL(change_codriver_temp(QVariant,QVariant,QVariant)), obj, SLOT(change_codriver_temp(QVariant,QVariant,QVariant)));

    //anzeige initialisieren
    int driver_temp = klima_logic_class->get_driver_temp();
    emit change_driver_temp(driver_temp,color_arr[6],color_border_arr[6]);

    int codriver_temp = klima_logic_class->get_codriver_temp();
    emit change_codriver_temp(codriver_temp,color_arr[6],color_border_arr[6]);

}

ClimateControlWidget::~ClimateControlWidget()
{
    delete ui;
    delete timer_klima;
    delete klima_logic_class;
}

void ClimateControlWidget::set_time()      //uhrzeit setzten
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void ClimateControlWidget::go_back()       //wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void ClimateControlWidget::driver_increase_temp()
{
    klima_logic_class->set_driver_temp(1);
    int driver_temp = klima_logic_class->get_driver_temp();
    QString color[2];
    get_color(driver_temp, color);
    emit change_driver_temp(driver_temp, color[0], color[1]);
    disable_button(0, driver_temp);
}
void ClimateControlWidget::driver_decrease_temp()
{
     klima_logic_class->set_driver_temp(-1);
     int driver_temp = klima_logic_class->get_driver_temp();
     QString color[2];
     get_color(driver_temp, color);
     emit change_driver_temp(driver_temp,color[0], color[1]);
     disable_button(0, driver_temp);
}
void ClimateControlWidget::codriver_increase_temp()
{
     klima_logic_class->set_codriver_temp(1);
     int codriver_temp = klima_logic_class->get_codriver_temp();
     QString color[2];
     get_color(codriver_temp, color);
     emit change_codriver_temp(codriver_temp,color[0], color[1]);
     disable_button(1, codriver_temp);

}
void ClimateControlWidget::codriver_decrease_temp()
{
     klima_logic_class->set_codriver_temp(-1);
     int codriver_temp = klima_logic_class->get_codriver_temp();
     QString color[2];
     get_color(codriver_temp, color);
     emit change_codriver_temp(codriver_temp,color[0], color[1]);
     disable_button(1, codriver_temp);
}

void ClimateControlWidget::get_color(int driver_temp, QString result[])
{
    QString c1 = "";
    QString c2 = "";
    if(driver_temp < 13)
    {
        c1 = color_arr[0];
        c2 = color_border_arr[0];
    }
    else if(driver_temp < 15)
    {
        c1 = color_arr[1];
        c2 = color_border_arr[1];
    }
    else if(driver_temp < 17)
    {
        c1 = color_arr[2];
        c2 = color_border_arr[2];
    }
    else if(driver_temp < 19)
    {
        c1 = color_arr[3];
        c2 = color_border_arr[3];
    }
    else if(driver_temp < 21)
    {
        c1 = color_arr[4];
        c2 = color_border_arr[4];
    }
    else if(driver_temp < 22)
    {
        c1 = color_arr[5];
        c2 = color_border_arr[5];
    }
    else if(driver_temp < 23)
    {
        c1 = color_arr[6];
        c2 = color_border_arr[6];
    }
    else if(driver_temp < 24)
    {
        c1 = color_arr[7];
        c2 = color_border_arr[7];
    }
    else if(driver_temp < 26)
    {
        c1 = color_arr[8];
        c2 = color_border_arr[8];
    }
    else if(driver_temp < 28)
    {
        c1 = color_arr[9];
        c2 = color_border_arr[9];
    }
    else if(driver_temp < 30)
    {
        c1 = color_arr[10];
        c2 = color_border_arr[10];
    }
    else if(driver_temp < 33)
    {
        c1 = color_arr[11];
        c2 = color_border_arr[11];
    }
    else
    {
        c1 = color_arr[12];
        c2 = color_border_arr[12];
    }
    result[0] = c1;
    result[1] = c2;
}

void ClimateControlWidget::disable_button(bool display, int temp)
{
    int i;
    if(display == 0)
        i = 0;
    else
        i = 2;
    if(klima_logic_class->disable_button_up(temp))
        arrow_buttons[i]->setEnabled(false);
    else
        arrow_buttons[i]->setEnabled(true);
    if(klima_logic_class->disable_button_down(temp))
        arrow_buttons[i+1]->setEnabled(false);
    else
        arrow_buttons[i+1]->setEnabled(true);
}

void ClimateControlWidget::off_button_pressed()
{
    klima_logic_class->toggle_off_state();
    if(klima_logic_class->get_off_state() == 1)
        off_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    else
        off_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
}

void ClimateControlWidget::auto_button_pressed()
{
    klima_logic_class->toggle_auto_state();
    if(klima_logic_class->get_auto_state() == 1)
        auto_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    else
        auto_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
}
void ClimateControlWidget::window_heater_button_pressed()
{
    klima_logic_class->toggle_window_heater_state();
    if(klima_logic_class->get_window_heater_state() == 1)
        window_heater_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    else
        window_heater_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
}
void ClimateControlWidget::seat_heater_button_pressed()
{
    klima_logic_class->toggle_seat_heater_state();
    if(klima_logic_class->get_seat_heater_state() == 1)
        seat_heater_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    else
        seat_heater_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
}
void ClimateControlWidget::ac_button_pressed()
{
    klima_logic_class->toggle_ac_state();
    if(klima_logic_class->get_ac_state() == 1)
        ac_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));");
    else
        ac_button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(81, 81, 81, 255), stop:1 rgba(255, 255, 255, 255));");
}


