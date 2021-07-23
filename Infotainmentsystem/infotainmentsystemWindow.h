#ifndef INFOTAINMENTSYSTEMWINDOW_H
#define INFOTAINMENTSYSTEMWINDOW_H

#include <QMainWindow>

#include "gui/navigationWidget.h"
#include "gui/vehicleWidget.h"
#include "gui/mediaPlayerWidget.h"
#include "gui/multimediaPlayerWidget.h"
#include "gui/settingsWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InfotainmentsystemWindow; }
QT_END_NAMESPACE

class InfotainmentsystemWindow : public QMainWindow
{
    Q_OBJECT

public:
    InfotainmentsystemWindow(QWidget *parent = nullptr);
    ~InfotainmentsystemWindow();
    void disp_navi();
    void disp_radio();
    void disp_phone();
    void disp_media();
    void update_backround();
    void stop_media_player();
    void stop_radio();
    void showHomeScreen();

public slots:
    void timerFunction();

private slots:
    void on_tb_Einstellungen_clicked();
    void on_tb_Radio_clicked();
    void on_tb_Navigation_clicked();
    void on_pb_Radio_clicked();
    void on_pb_Navigation_clicked();
    void on_tb_Fahrzeug_clicked();
    void on_tb_Medien_clicked();
    void on_pushButton_12_clicked();

private:
    Ui::InfotainmentsystemWindow *ui;
    QTimer *timer;
    MultimediaPlayerWidget* radio;
    NavigationWidget* navigation;
    VehicleWidget* fahrzeug;
    SettingsWidget* einstellungen;
    MediaPlayerWidget* media_player;

};
#endif // INFOTAINMENTSYSTEMWINDOW_H
