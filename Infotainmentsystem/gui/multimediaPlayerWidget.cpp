#include "multimediaPlayerWidget.h"
#include "ui_MultimediaPlayerWidget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QDateTime>
#include <QTimer>


#include "infotainmentsystemWindow.h"


MultimediaPlayerWidget::MultimediaPlayerWidget(InfotainmentsystemWindow *menu, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MultimediaPlayerWidget)
{
    menu_obj = menu;
    infotainmentsystem_obj = menu;

    ui->setupUi(this);

    //Logic Klasse Initialisieren
    mediaplayer_logic = new MultimediaPlayer(this);

    //Timer zum aktualisieren der Uhrzeit starten
    timer_radio = new QTimer(this);
    connect(timer_radio, &QTimer::timeout, this, &MultimediaPlayerWidget::set_time);
    timer_radio->start(1000);

    //Anzahl der gespeicherten Sender einlesen
    channel_buttons = new QPushButton*[mediaplayer_logic->get_channel_nr()];

    //Default Radio Channel Pushbuttons in Pointerarray speichern
    channel_buttons[0] = MultimediaPlayerWidget::findChild<QPushButton *>("Button1");
    channel_buttons[1] = MultimediaPlayerWidget::findChild<QPushButton *>("Button2");
    channel_buttons[2] = MultimediaPlayerWidget::findChild<QPushButton *>("Button3");
    channel_buttons[3] = MultimediaPlayerWidget::findChild<QPushButton *>("Button4");
    channel_buttons[4] = MultimediaPlayerWidget::findChild<QPushButton *>("Button5");

    //Weitere Pushbuttons (HOme & Addfav) verbinden
    addfav = MultimediaPlayerWidget::findChild<QToolButton *>("addfav");
    QObject::connect(addfav,&QToolButton::clicked, this, &MultimediaPlayerWidget::add_favourite);
    HomeButton = MultimediaPlayerWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(HomeButton,&QPushButton::clicked, this, &MultimediaPlayerWidget::go_home);

    //Radio Channels mit channel selected slot connecten, wenn button gedrückt wird
    QObject::connect(channel_buttons[0],&QPushButton::clicked, this, &MultimediaPlayerWidget::channel_selected);
    QObject::connect(channel_buttons[1],&QPushButton::clicked, this, &MultimediaPlayerWidget::channel_selected);
    QObject::connect(channel_buttons[2],&QPushButton::clicked, this, &MultimediaPlayerWidget::channel_selected);
    QObject::connect(channel_buttons[3],&QPushButton::clicked, this, &MultimediaPlayerWidget::channel_selected);
    QObject::connect(channel_buttons[4],&QPushButton::clicked, this, &MultimediaPlayerWidget::channel_selected);

    //Side Menu PushButtons verknüpfen
    side_menu[0] = MultimediaPlayerWidget::findChild<QPushButton *>("pb_Menu");
    side_menu[1] = MultimediaPlayerWidget::findChild<QPushButton *>("pb_Radio");
    side_menu[2] = MultimediaPlayerWidget::findChild<QPushButton *>("pb_Media");
    side_menu[3] = MultimediaPlayerWidget::findChild<QPushButton *>("pb_Phone");
    side_menu[4] = MultimediaPlayerWidget::findChild<QPushButton *>("pb_Navigation");

    //Side Menu Pbs mit entsprechenden Slots zum öffnen des neuen Fensters verknüpfen (außer PB1, da bereits Radio ausgewählt)
    QObject::connect(side_menu[0],&QPushButton::clicked, this, &MultimediaPlayerWidget::side_menu_clicked);
    QObject::connect(side_menu[2],&QPushButton::clicked, this, &MultimediaPlayerWidget::side_menu_clicked);
    QObject::connect(side_menu[3],&QPushButton::clicked, this, &MultimediaPlayerWidget::side_menu_clicked);
    QObject::connect(side_menu[4],&QPushButton::clicked, this, &MultimediaPlayerWidget::side_menu_clicked);

    //Radio Side menu Button orange färben
    side_menu[1]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));border-color: rgb(255, 255, 255);border-width: 1.2px; border-style:inset; color: rgb(255, 255, 255);");

    //Popupwindow für Eingabe eines neuen Favoritens einrichten
    popupwindow = new AddNewFavouriteWidget(mediaplayer_logic, this);
    QObject::connect(popupwindow, &AddNewFavouriteWidget::favourite_added_signal, this, &MultimediaPlayerWidget::initialize_new_favourite);

    //Popupwindow zum Bestätigen der Löschung aller hinzugefügtenn Favoriten
    popupwindow2 = new ConfirmFavDeletionWidget(this);

    //Lautstärkeregler initialiseren
    volume_adjuster = MultimediaPlayerWidget::findChild<QSlider *>("horizontalSlider");
    QObject::connect(volume_adjuster,&QSlider::valueChanged, this, &MultimediaPlayerWidget::set_volume);
    ui->label_volume->setText(QString::number(mediaplayer_logic->get_volume())+QString("%"));

    //Mute Button initialisieren
    mute_button = MultimediaPlayerWidget::findChild<QPushButton *>("MuteButton");
    QObject::connect(mute_button,&QPushButton::clicked, this, &MultimediaPlayerWidget::mute);

    //Delete Button initialisieren
    DeleteButton = MultimediaPlayerWidget::findChild<QPushButton *>("DeleteButton");
    QObject::connect(DeleteButton,&QPushButton::clicked, this, &MultimediaPlayerWidget::delete_favs);

    //Label zur Angaben der Favoritenanzahl beschreiben
    ui->label_fav->setText(QString::number(mediaplayer_logic->get_channel_nr()-5)+"/5");


}

MultimediaPlayerWidget::~MultimediaPlayerWidget()
{
    delete ui;
    delete [] channel_buttons;
    delete timer_radio;
    delete popupwindow;
    delete popupwindow2;
    delete mediaplayer_logic;
}

void MultimediaPlayerWidget::channel_selected()      //Slot, wenn PB für Sender gedrückt wird
{

    //Media Player stoppen, falls dieser läuft
    infotainmentsystem_obj->stop_media_player();

    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();

    //Farbe des gewählten Buttons ändern
    button->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));font-size: 38px;height: 120px;width: 120px;");

    if(mediaplayer_logic->get_prev_channel() != nullptr&&mediaplayer_logic->get_player_status() == 1)
    {
        //Farbe des vorherigen Buttons zurücksetzen
        mediaplayer_logic->get_prev_channel()->setStyleSheet("background-color: rgb(255, 255, 255);font-size: 38px;height: 120px;width: 120px;");
    }

    //Weitergabe des aktivierten Buttons an die Logic Klasse
    mediaplayer_logic->channel_selected(button_name, button);

    return;
}

void MultimediaPlayerWidget::add_favourite() //Slot, wenn PB für "neuen Favoriten hinzufügen" gedrückt wird
{
    //Popupwindow zeigen
    popupwindow->setModal(true);
    popupwindow->prepare_window();
    popupwindow->show();
}

void MultimediaPlayerWidget::initialize_new_favourite()  //Funktion um neuen Favouriten zu initialisieren, wird getriggert durch signal aus AddNewFavouriteWidget
{
    QString fav_name = popupwindow->getname();   //eingegebenen Name und URL aus popupwindow einlesen
    QString fav_url = popupwindow->geturl();

    mediaplayer_logic->initialize_new_favourite(fav_url, fav_name);

    QPushButton** ptemp1 = new QPushButton*[mediaplayer_logic->get_channel_nr()];        //neue vergrößerte arrays anlegen


    for(int i = 0; i<mediaplayer_logic->get_channel_nr()-1;i++)  //kopieren der alten array werte in die neuen arrays
    {
        ptemp1[i] = channel_buttons[i];
    }

    delete [] channel_buttons;      //löschen der alten arrays

    channel_buttons = ptemp1;

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->verticalFrame->layout());     //layout finden, auf dem neuer button angelegt werden soll
    QPushButton *new_fav_button = new QPushButton(ui->centralwidget);               //neuen push button erzeugen
    new_fav_button->setStyleSheet("background-color: rgb(255, 255, 255);font-size: 38px;height: 120px;width: 120px;");
    new_fav_button->setText(fav_name);                                              //test des neuen push buttons setzen                              //objektnamen setzen
    new_fav_button->setObjectName("Button"+QString::number(mediaplayer_logic->get_channel_nr()));            //Objektnamen setzen
    channel_buttons[mediaplayer_logic->get_channel_nr()-1] = new_fav_button;                                 //button zum button array hinzufügen
    layout->addWidget(new_fav_button);                                              //neuen button zu layout hinzufügen
    QObject::connect(channel_buttons[mediaplayer_logic->get_channel_nr()-1],&QPushButton::clicked, this, &MultimediaPlayerWidget::channel_selected);  //mit methode channel_selected verknüpfen, falls neuer push button geklickt wird

    ui->label_fav->setText(QString::number(mediaplayer_logic->get_channel_nr()-5)+"/5");              //Favoriten Label anpassen
}

void MultimediaPlayerWidget::go_home()       //wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void MultimediaPlayerWidget::set_time()  //aktualisieren der aktuellen UHrzeit
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void MultimediaPlayerWidget::set_volume()    //Slot wird aufgerufen, wenn Lautstärken silder verändert wird
{
    int volume = volume_adjuster->value();
    mediaplayer_logic->set_volume(volume);
    ui->label_volume->setText(QString::number(mediaplayer_logic->get_volume())+QString("%"));
}


void MultimediaPlayerWidget::mute()      //Slot wird aufgerufen, wenn Mute Button gedrückt wird
{
    //Farbe des Buttons anpassen
    if(mediaplayer_logic->get_mute_state() == 0)
    {
        mute_button->setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));border-width: 5px;border-radius: 10px;}QPushButton:pressed {border-color: rgb(0, 0, 0);border-width : 1.2px;border-style:inset;}");
    }
    else
    {
        mute_button->setStyleSheet("QPushButton{background-color: rgb(255, 255, 255);border-width: 5px;border-radius: 10px;}QPushButton:pressed {border-color: rgb(0, 0, 0);border-width : 1.2px;border-style:inset;}");
    }

    //Logik klasse informieren, dass mute button gedrück wurde
    mediaplayer_logic->mute();
}

int MultimediaPlayerWidget::get_channel_nr() //Information über Anzahl der Channel Anzahl zurückgeben
{
    return mediaplayer_logic->get_channel_nr();
}

void MultimediaPlayerWidget::delete_favs()   //Slot wird aufgerufen, wenn Papierkorb Icon aktiviert wird
{
    //Popupwindow zeigen
    popupwindow2->setModal(true);
    popupwindow2->show();
}

void MultimediaPlayerWidget::delete_favs_confirmed()   //Favoritenliste löschen, wenn Bestätigung der Abfrage
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->verticalFrame->layout());
    QString obj_name;
    QPushButton* button;
    for(int i = mediaplayer_logic->get_channel_nr();i>5;i--){
        obj_name = "Button"+QString::number(i);
        button = MultimediaPlayerWidget::findChild<QPushButton *>(obj_name);
        layout->removeWidget(button);
        delete button;
    }
    mediaplayer_logic->set_channel_nr(5);
    ui->label_fav->setText("0/5");
}

void MultimediaPlayerWidget::side_menu_clicked() //Slot wird aufgerufen, wenn einer der Side Menu Buttons gedrückt wird
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();
    qInfo() << button_name << " pressed";

    //Überprüfen, welcher Button gedrückt wurde und entsprechendes Fenster anzeigen
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
    if(button_name == side_menu[4]->objectName())
    {
        infotainmentsystem_obj->disp_navi();
    }
    return;
}

void MultimediaPlayerWidget::stop_Player()  //Methode wird aufgerufen, wenn Media Player Musik abspielen soll, damit Radio gestoppt wird
{
    if(mediaplayer_logic->get_prev_channel() != nullptr)
        mediaplayer_logic->get_prev_channel()->setStyleSheet("background-color: rgb(255, 255, 255);font-size: 38px;height: 120px;width: 120px;");
    mediaplayer_logic->stop();
}
