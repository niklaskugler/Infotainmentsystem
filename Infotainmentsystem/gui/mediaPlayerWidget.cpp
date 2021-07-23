#include "ui_mediaPlayerWidget.h"

#include "infotainmentsystemWindow.h"
#include "gui/mediaPlayerWidget.h"

#include <QDateTime>
#include <QTimer>
#include <sstream>
#include <iomanip>

MediaPlayerWidget::MediaPlayerWidget(InfotainmentsystemWindow *menu, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaPlayerWidget)
{
    ui->setupUi(this);

    menu_obj = menu;
    infotainmentsystem_obj = menu;

    //Logic Klasse Initialisieren
    mediaplayer_logic = new MediaPlayer(this);

    current_max = 0;    //Maximale Zeit eines Tracks - wird später überschrieben

    //Timer zum aktualisieren der Uhrzeit starten
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MediaPlayerWidget::set_time);
    timer->start(1000);

    //Weitere Pushbuttons (HOme & Addfav) verbinden
    HomeButton = MediaPlayerWidget::findChild<QPushButton *>("HomeButton");
    QObject::connect(HomeButton,&QPushButton::clicked, this, &MediaPlayerWidget::go_home);

    //Side Menu PushButtons verknüpfen
    side_menu[0] = MediaPlayerWidget::findChild<QPushButton *>("pb_Menu");
    side_menu[1] = MediaPlayerWidget::findChild<QPushButton *>("pb_Radio");
    side_menu[2] = MediaPlayerWidget::findChild<QPushButton *>("pb_Media");
    side_menu[3] = MediaPlayerWidget::findChild<QPushButton *>("pb_Phone");
    side_menu[4] = MediaPlayerWidget::findChild<QPushButton *>("pb_Navigation");

    //Side Menu Pbs mit entsprechenden Slots zum öffnen des neuen Fensters verknüpfen (außer PB1, da bereits Radio ausgewählt)
    QObject::connect(side_menu[0],&QPushButton::clicked, this, &MediaPlayerWidget::side_menu_clicked);
    QObject::connect(side_menu[1],&QPushButton::clicked, this, &MediaPlayerWidget::side_menu_clicked);
    QObject::connect(side_menu[3],&QPushButton::clicked, this, &MediaPlayerWidget::side_menu_clicked);
    QObject::connect(side_menu[4],&QPushButton::clicked, this, &MediaPlayerWidget::side_menu_clicked);

    //Radio Side menu Button orange färben
    side_menu[2]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 170, 0, 255), stop:1 rgba(255, 255, 255, 255));border-color: rgb(255, 255, 255);border-width: 1.2px; border-style:inset; color: rgb(255, 255, 255);");

    //Lautstärkeregler initialiseren
    volume_adjuster = MediaPlayerWidget::findChild<QSlider *>("horizontalSlider");
    QObject::connect(volume_adjuster,&QSlider::valueChanged, this, &MediaPlayerWidget::set_volume);
    ui->label_volume->setText(QString::number(mediaplayer_logic->get_volume())+QString("%"));

    //Musikregler initialiseren
    progress_slider = MediaPlayerWidget::findChild<QSlider *>("progress_slider");

    //Slots für Progress Bar einrichten
    QObject::connect(progress_slider,&QSlider::sliderMoved, this, &MediaPlayerWidget::change_time);

    //Mute Button initialisieren
    mute_button = MediaPlayerWidget::findChild<QPushButton *>("MuteButton");
    QObject::connect(mute_button,&QPushButton::clicked, this, &MediaPlayerWidget::mute);

    //Pointern zu Play, next und back button in array speichern
    control_buttons[0] = MediaPlayerWidget::findChild<QPushButton *>("pb_back");
    control_buttons[1] = MediaPlayerWidget::findChild<QPushButton *>("pb_pause");
    control_buttons[2] = MediaPlayerWidget::findChild<QPushButton *>("pb_next");

    //Play, next und back button mit slot verbinden
    QObject::connect(control_buttons[0],&QPushButton::clicked, this, &MediaPlayerWidget::control_button_clicked);
    QObject::connect(control_buttons[1],&QPushButton::clicked, this, &MediaPlayerWidget::control_button_clicked);
    QObject::connect(control_buttons[2],&QPushButton::clicked, this, &MediaPlayerWidget::control_button_clicked);

    //Media Player cover icons in array lesen
    song_cover_img[0] = ":/Images/Music_Lieder_Tawil.jpg";
    song_cover_img[1] = ":/Images/Music_Pompeii_Bastille.jpg";
    song_cover_img[2] = ":/Images/Music_Lieder_counting_stars.jpg";

    //Media Player Song Titel & Interpreten einlesen
    song_title[0] = "Lieder - Adel Tawil";
    song_title[1] = "Pompeii - Bastille";
    song_title[2] = "Counting Stars - One Republic";

    ui->label_track_name->setText(song_title[0]);
    ui->label_track_name->setAlignment(Qt::AlignCenter);
    ui->label_current_time->setText("00:00");
}

MediaPlayerWidget::~MediaPlayerWidget()
{
    delete ui;
    delete timer;
    delete mediaplayer_logic;
}

void MediaPlayerWidget::go_home()       //wird beim betätigen des home buttons ausgelöst
{
    emit homeButtonClicked();
}

void MediaPlayerWidget::set_time()  //aktualisieren der aktuellen UHrzeit
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void MediaPlayerWidget::side_menu_clicked() //Slot wird aufgerufen, wenn einer der Side Menu Buttons gedrückt wird
{
    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();
    qInfo() << button_name << " pressed";

    //Überprüfen, welcher Button gedrückt wurde und entsprechendes Fenster anzeigen
    if(button_name == side_menu[0]->objectName())
    {
        infotainmentsystem_obj->showHomeScreen();
    }
    if(button_name == side_menu[1]->objectName())
    {
        infotainmentsystem_obj->disp_radio();
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

void MediaPlayerWidget::set_volume()    //Slot wird aufgerufen, wenn Lautstärken silder verändert wird
{
    int volume = volume_adjuster->value();
    mediaplayer_logic->set_volume(volume);
    ui->label_volume->setText(QString::number(mediaplayer_logic->get_volume())+QString("%"));
}


void MediaPlayerWidget::mute()      //Slot wird aufgerufen, wenn Mute Button gedrückt wird
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

void MediaPlayerWidget::control_button_clicked()     //Slot, welcher aufgeruden wird, wenn einer der drei Control Buttons (Play, next, back) gedrückt wird
{

    infotainmentsystem_obj->stop_radio();   //radio stoppen, falls dieses noch läuft

    QPushButton *button = (QPushButton *)sender();
    QString button_name = button->objectName();

    if(button_name == control_buttons[1]->objectName())
    {
        mediaplayer_logic->play();
        if (mediaplayer_logic->get_player_status() == true)     //icon des play/pause buttons anpassen
        {
            QPixmap pixmap(":/Images/pause_icon.png");
            QIcon ButtonIcon(pixmap);
            control_buttons[1]->setIcon(ButtonIcon);
        }
        else
        {
            QPixmap pixmap(":/Images/play_icon.png");
            QIcon ButtonIcon(pixmap);
            control_buttons[1]->setIcon(ButtonIcon);
        }
        return;
    }
    int index = 0;
    if(button_name == control_buttons[0]->objectName())
    {
        index = mediaplayer_logic->back();

    }
    if(button_name == control_buttons[2]->objectName())
    {
        index = mediaplayer_logic->next();
    }
    QPixmap pixmap(song_cover_img[index%3]);    //Anzeige des Covers aktualisieren
    ui->track_image_label->setPixmap(pixmap);

    //Set label of new song name
    ui->label_track_name->setText(song_title[index%3]);
}

void MediaPlayerWidget::stop_Player()    //Wird von Radio aufgerufen, wenn dort ein Channel ausgesucht wird.
{
    if (mediaplayer_logic->get_player_status() == true)   //wenn player gerade läuft, diesen pausieren
    {
       mediaplayer_logic->play();
       QPixmap pixmap(":/Images/play_icon.png");
       QIcon ButtonIcon(pixmap);
       control_buttons[1]->setIcon(ButtonIcon);
    }
}

void MediaPlayerWidget::change_time()
{
    int time = progress_slider->value();
    mediaplayer_logic->change_time(time);
}

void MediaPlayerWidget::change_position(qint64 position)
{
    progress_slider->setValue(position);    //set silder to new position

    int sekunden = (position / 1000) % 60;      //print past time on screen
    int minuten = (position / 1000) / 60;
    std::stringstream sekunden_str;
    sekunden_str << std::setw(2) << std::setfill('0') << sekunden;
    std::string sekunden_s = sekunden_str.str();

    std::stringstream minuten_str;
    minuten_str << std::setw(2) << std::setfill('0') << minuten;
    std::string minuten_s = minuten_str.str();

    QString qstr = QString::fromUtf8((minuten_s+":"+sekunden_s).c_str());
    ui->label_current_time->setText(qstr);


    if(position == current_max && mediaplayer_logic->get_player_status() == 1 && current_max != 0)
    {
        int index = mediaplayer_logic->next();
        QPixmap pixmap(song_cover_img[index%3]);    //Anzeige des Covers aktualisieren
        ui->track_image_label->setPixmap(pixmap);

        //Set label of new song name
        ui->label_track_name->setText(song_title[index%3]);
    }
}

void MediaPlayerWidget::change_duration(qint64 position)
{
    progress_slider->setMaximum(position);      //set max position of slider

    current_max = position;

    int sekunden = (position / 1000) % 60;      //print total time on screen
    int minuten = (position / 1000) / 60;
    std::stringstream sekunden_str;
    sekunden_str << std::setw(2) << std::setfill('0') << sekunden;
    std::string sekunden_s = sekunden_str.str();

    std::stringstream minuten_str;
    minuten_str << std::setw(2) << std::setfill('0') << minuten;
    std::string minuten_s = minuten_str.str();

    QString qstr = QString::fromUtf8((minuten_s+":"+sekunden_s).c_str());

    ui->label_max_time->setText(qstr);
}
