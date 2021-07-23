#ifndef CLIMATECONTROL_H
#define CLIMATECONTROL_H

#include <QObject>

class ClimateControl : public QObject
{
    Q_OBJECT

public:
    explicit ClimateControl(QObject *parent = nullptr);
    int get_driver_temp();
    int get_codriver_temp();
    void set_driver_temp(int temp);
    void set_codriver_temp(int temp);
    int get_max_temp();
    int get_min_temp();
    bool disable_button_up(int temp);
    bool disable_button_down(int temp);
    bool get_off_state();
    bool get_auto_state();
    bool get_window_heater_state();
    bool get_seat_heater_state();
    bool get_ac_state();
    void toggle_off_state();
    void toggle_auto_state();
    void toggle_window_heater_state();
    void toggle_seat_heater_state();
    void toggle_ac_state();

private:
    int driver_temp;
    int codriver_temp;
    int max_temp;
    int min_temp;
    bool off_state;
    bool auto_state;
    bool window_heater_state;
    bool seat_heater_state;
    bool ac_state;
};

#endif // CLIMATECONTROL_H
