#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

#include "core/settings.h"

class InfotainmentsystemWindow;
class QPushButton;
class QTimer;

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(InfotainmentsystemWindow* menu, QWidget *parent = nullptr);
    ~SettingsWidget();

private:
    Ui::SettingsWidget *ui;
    QTimer *timer;
    QWidget* menu_obj;
    QPushButton* HomeButton;
    QPushButton *side_menu[5];
    QPushButton *color_selection[6];
    InfotainmentsystemWindow* infotainmentsystem_obj;
    Settings* logic_class;

private slots:
    void set_time();
    void go_home();
    void side_menu_clicked();
    void backround_selected();

signals:
    void homeButtonClicked();
};

#endif // SETTINGSWIDGET_H
