#ifndef CLIMATECONTROLWIDGET_H
#define CLIMATECONTROLWIDGET_H

#include <QWidget>
#include <QVariant>

#include "gui/climateControlWidget.h"

class ClimateControl;
class QPushButton;

namespace Ui {
class ClimateControlWidget;
}

class ClimateControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClimateControlWidget(QWidget *parent = nullptr);
    ~ClimateControlWidget();
    void get_color(int driver_temp, QString result[]);
    void disable_button(bool display, int temp);

private:
    Ui::ClimateControlWidget *ui;
    QWidget* parent_obj;
    QTimer *timer_klima;
    QPushButton* BackButton;
    QPushButton* arrow_buttons[4];   //Array enthält arrow buttons der klima gui
    ClimateControl* klima_logic_class;
    QString color_arr[13];
    QString color_border_arr[13];
    QPushButton* off_button;
    QPushButton* auto_button;
    QPushButton* window_heater_button;
    QPushButton* seat_heater_button;
    QPushButton* ac_button;

 private slots:
    void set_time();
    void go_back();
    void driver_increase_temp();
    void driver_decrease_temp();
    void codriver_increase_temp();
    void codriver_decrease_temp();
    void off_button_pressed();
    void auto_button_pressed();
    void window_heater_button_pressed();
    void seat_heater_button_pressed();
    void ac_button_pressed();

signals:
    void change_codriver_temp(QVariant codriver_temp, QVariant color, QVariant border_color);
    void change_driver_temp(QVariant driver_temp, QVariant color, QVariant border_color);
    void homeButtonClicked();

};

#endif // CLIMATECONTROLWIDGET_H
