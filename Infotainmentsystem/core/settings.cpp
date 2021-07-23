#include "settings.h"
#include "global_variables.h"

QString backround_color;

Settings::Settings(QObject *parent) : QObject(parent)
{
    //Farbpalette für den Hintergrund setzen
    color_palette[0] = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(91, 91, 91, 255));";
    color_palette[1] = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 253, 255), stop:1 rgba(0, 0, 0, 255));";
    color_palette[2] = "background-color: rgb(0, 0, 0);";
    color_palette[3] = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 90, 0, 255), stop:1 rgba(255, 255, 255, 255));";
    color_palette[4] = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(86, 84, 84, 255), stop:1 rgba(255, 255, 255, 255));";
    color_palette[5] = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(153, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));";

    backround_color = color_palette[0];
}

void Settings::update_color(int x)
{
    backround_color = color_palette[x];
}
