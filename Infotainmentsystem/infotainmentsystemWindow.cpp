#include "infotainmentsystemWindow.h"
#include "ui_InfotainmentsystemWindow.h"

#include <QDateTime>
#include <QTimer>

#include "core/global_variables.h"


InfotainmentsystemWindow::InfotainmentsystemWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfotainmentsystemWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerFunction()));
    timer->start(1000);
    radio = new MultimediaPlayerWidget(this);
    connect(radio, &MultimediaPlayerWidget::homeButtonClicked, this, &InfotainmentsystemWindow::showHomeScreen);
    ui->page_radio->layout()->addWidget(radio);

    navigation = new NavigationWidget(this);
    connect(navigation, &NavigationWidget::homeButtonClicked, this, &InfotainmentsystemWindow::showHomeScreen);
    ui->page_navigation->layout()->addWidget(navigation);

    fahrzeug = new VehicleWidget(this);
    connect(fahrzeug, &VehicleWidget::homeButtonClicked, this, &InfotainmentsystemWindow::showHomeScreen);
    ui->page_vehicle->layout()->addWidget(fahrzeug);

    einstellungen = new SettingsWidget(this);
    connect(einstellungen, &SettingsWidget::homeButtonClicked, this, &InfotainmentsystemWindow::showHomeScreen);
    ui->page_settings->layout()->addWidget(einstellungen);

    media_player = new MediaPlayerWidget(this);
    connect(media_player, &MediaPlayerWidget::homeButtonClicked, this, &InfotainmentsystemWindow::showHomeScreen);
    ui->page_mediaPlayer->layout()->addWidget(media_player);
}

InfotainmentsystemWindow::~InfotainmentsystemWindow()
{
    delete ui;
}

void InfotainmentsystemWindow::timerFunction()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm");
    ui->label_date_time->setText(time_text);
}

void InfotainmentsystemWindow::on_tb_Radio_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_radio);
}

void InfotainmentsystemWindow::on_tb_Navigation_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_navigation);
}

void InfotainmentsystemWindow::on_pb_Radio_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_radio);
}

void InfotainmentsystemWindow::on_pb_Navigation_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_navigation);
}

void InfotainmentsystemWindow::on_tb_Fahrzeug_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_vehicle);
}

void InfotainmentsystemWindow::on_tb_Einstellungen_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_settings);
}

void InfotainmentsystemWindow::on_tb_Medien_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_mediaPlayer);
}

void InfotainmentsystemWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_mediaPlayer);
}

void InfotainmentsystemWindow::showHomeScreen()
{
    ui->stackedWidget->setCurrentWidget(ui->page_start);
}

void InfotainmentsystemWindow::disp_navi()
{
    ui->stackedWidget->setCurrentWidget(ui->page_navigation);
}
void InfotainmentsystemWindow::disp_radio()
{
    ui->stackedWidget->setCurrentWidget(ui->page_radio);
}

void InfotainmentsystemWindow::disp_phone()
{
    //to be done
    return;
}
void InfotainmentsystemWindow::disp_media()
{
    ui->stackedWidget->setCurrentWidget(ui->page_mediaPlayer);
}

void InfotainmentsystemWindow::update_backround()
{
    this->setStyleSheet(backround_color);
    navigation->setStyleSheet(backround_color);
    radio->setStyleSheet(backround_color);
    fahrzeug->setStyleSheet(backround_color);
    einstellungen->setStyleSheet(backround_color);
    fahrzeug->update_backround();
    media_player->setStyleSheet(backround_color);
}

void InfotainmentsystemWindow::stop_media_player()
{
    media_player->stop_Player();
}

void InfotainmentsystemWindow::stop_radio()
{
    radio->stop_Player();
}
