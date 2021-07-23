#ifndef DRIVEMODEWIDGET_H
#define DRIVEMODEWIDGET_H

#include <QWidget>

class QPushButton;
class QTimer;

namespace Ui {
class DriveModeWidget;
}

class DriveModeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DriveModeWidget(QWidget *parent = nullptr);
    ~DriveModeWidget();
    void deactivate_all();

private:
    Ui::DriveModeWidget *ui;
    QWidget* parent_obj;
    QTimer *timer_fahrmodus;
    QPushButton* BackButton;
    QPushButton* drivemode_buttons[4];
    bool efficiency_status;
    bool comfort_status;
    bool auto_status;
    bool dynamic_status;

private slots:
    void set_time();
    void go_back();
    void efficiency_mode();
    void comfort_mode();
    void auto_mode();
    void dynamic_mode();

signals:
    void change_rot_angle();
    void homeButtonClicked();
};

#endif // DRIVEMODEWIDGET_H
