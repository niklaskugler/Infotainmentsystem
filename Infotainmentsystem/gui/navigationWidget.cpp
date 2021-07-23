#include "NavigationWidget.h"
#include "ui_NavigationWidget.h"

#include "infotainmentsystemWindow.h"

#include <QQuickItem>

NavigationWidget::NavigationWidget(InfotainmentsystemWindow *menu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NavigationWidget)
{
    //parent_obj = parent;
    ui->setupUi(this);

    menu_obj = menu;
    infotainmentsystem_obj = menu;

    // navigieren zum Hauptmenü mit HomeButton
    HomeButton = NavigationWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(HomeButton,&QPushButton::clicked, this, &NavigationWidget::go_home);

    // Verlinkung zum einegebetten QuickWidget für das Navi
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/qml/map.qml")));

    //Side Menu PushButtons verknüpfen
    side_menu[0] = NavigationWidget::findChild<QPushButton *>("pb_Menu");
    side_menu[1] = NavigationWidget::findChild<QPushButton *>("pb_Radio");
    side_menu[2] = NavigationWidget::findChild<QPushButton *>("pb_Media");
    side_menu[3] = NavigationWidget::findChild<QPushButton *>("pb_Phone");
    side_menu[4] = NavigationWidget::findChild<QPushButton *>("pb_Navigation");

    //Side Menu Pbs mit entsprechenden Slots zum öffnen des neuen Fensters verknüpfen (außer PB1, da bereits Radio ausgewählt)
    QObject::connect(side_menu[0],&QPushButton::clicked, this, &NavigationWidget::side_menu_clicked);
    QObject::connect(side_menu[2],&QPushButton::clicked, this, &NavigationWidget::side_menu_clicked);
    QObject::connect(side_menu[3],&QPushButton::clicked, this, &NavigationWidget::side_menu_clicked);
    QObject::connect(side_menu[1],&QPushButton::clicked, this, &NavigationWidget::side_menu_clicked);

    //Dario Side menu Button orange färben
    side_menu[4]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));border-color: rgb(255, 255, 255);border-width: 1.2px; border-style:inset; color: rgb(255, 255, 255);");
}

NavigationWidget::~NavigationWidget()
{
    delete ui;
}

void NavigationWidget::go_home()
{
    // ausgelöst wenn homeButton betätigt wird
    emit homeButtonClicked();
}


void NavigationWidget::side_menu_clicked()
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();
    qInfo() << button_name << " pressed";
    if(button_name == side_menu[0]->objectName())
    {
        infotainmentsystem_obj->showHomeScreen();
    }
    if(button_name == side_menu[2]->objectName())
    {
        infotainmentsystem_obj->disp_media();
    }
    if(button_name == side_menu[3]->objectName())
    {
        infotainmentsystem_obj->disp_phone();
    }
    if(button_name == side_menu[1]->objectName())
    {
        infotainmentsystem_obj->disp_radio();
    }
    return;
}
