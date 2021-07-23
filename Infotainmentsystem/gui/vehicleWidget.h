#ifndef VEHICLEWIDGET_H
#define VEHICLEWIDGET_H

#include <QObject>

#include "gui/climateControlWidget.h"
#include "gui/driveModeWidget.h"
#include "gui/driveAssistWidget.h"

class InfotainmentsystemWindow;
class QPushButton;
class QTimer;
class QToolButton;

namespace Ui {
class VehicleWidget;
}

class VehicleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleWidget(InfotainmentsystemWindow* menu, QWidget *parent = nullptr);
    ~VehicleWidget();
    void update_backround();

private:
    Ui::VehicleWidget *ui;
    QTimer *timer_fahrzeug;
    QWidget* menu_obj;
    QPushButton* HomeButton;
    QToolButton* fahrmodus_button;
    QToolButton* klima_button;
    QToolButton* fahrerassistenz_button;
    ClimateControlWidget* klima_obj;
    DriveModeWidget* fahrmodus_obj;
    DriveAssistWidget* fahrerassistenz_obj;
    QPushButton *side_menu[5];
    InfotainmentsystemWindow* infotainmentsystem_obj;

private slots:
    void set_time();
    void go_home();
    void display_fahrmodus();
    void display_klima();
    void display_fahrerassistenz();
    void side_menu_clicked();
    void showMainMenu();

signals:
    void homeButtonClicked();
};

#endif // VEHICLEWIDGET_H
