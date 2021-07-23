#include "climateControl.h"
#include <QDebug>

ClimateControl::ClimateControl(QObject *parent) : QObject(parent)
{
    driver_temp = 22;
    codriver_temp = 22;
    max_temp = 36;
    min_temp = 12;
    off_state = 0;
    auto_state = 0;
    window_heater_state = 0;
    seat_heater_state = 0;
    ac_state = 0;
}

int ClimateControl::get_driver_temp()
{
    return driver_temp;
}

int ClimateControl::get_codriver_temp()
{
    return codriver_temp;
}

void ClimateControl::set_driver_temp(int temp)
{
    if(driver_temp+temp <= max_temp && driver_temp+temp >= min_temp)
        driver_temp += temp;
}

void ClimateControl::set_codriver_temp(int temp)
{
   if(codriver_temp+temp <= max_temp && codriver_temp+temp >= min_temp)
        codriver_temp += temp;
}

int ClimateControl::get_max_temp()
{
    return max_temp;
}

int ClimateControl::get_min_temp()
{
    return min_temp;
}

bool ClimateControl::disable_button_up(int temp)
{
    if(temp == max_temp)
        return true;
    return false;
}
bool ClimateControl::disable_button_down(int temp)
{
    if(temp == min_temp)
        return true;
    return false;
}

bool ClimateControl::get_off_state()
{
    return off_state;
}

void ClimateControl::toggle_off_state()
{
    if(off_state == 0)
        off_state = 1;
    else
        off_state = 0;
}

bool ClimateControl::get_auto_state()
{
    return auto_state;
}

void ClimateControl::toggle_auto_state()
{
    if(auto_state == 0)
        auto_state = 1;
    else
        auto_state = 0;
}

bool ClimateControl::get_window_heater_state()
{
    return window_heater_state;
}

void ClimateControl::toggle_window_heater_state()
{
    if(window_heater_state == 0)
        window_heater_state = 1;
    else
        window_heater_state = 0;
}

bool ClimateControl::get_seat_heater_state()
{
    return seat_heater_state;
}

void ClimateControl::toggle_seat_heater_state()
{
    if(seat_heater_state == 0)
        seat_heater_state = 1;
    else
        seat_heater_state = 0;
}

bool ClimateControl::get_ac_state()
{
    return ac_state;
}

void ClimateControl::toggle_ac_state()
{
    if(ac_state == 0)
        ac_state = 1;
    else
        ac_state = 0;
}
