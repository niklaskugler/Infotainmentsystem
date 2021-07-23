#ifndef DRIVEASSISTWIDGET_H
#define DRIVEASSISTWIDGET_H

#include <QWidget>

class QPushButton;
class QTimer;

namespace Ui {
class DriveAssistWidget;
}

class DriveAssistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DriveAssistWidget(QWidget *parent = nullptr);
    ~DriveAssistWidget();

private:
    Ui::DriveAssistWidget *ui;
    QWidget* parent_obj;
    QTimer *timer_fahrmodus;
    QPushButton* BackButton;
    QPushButton* sound_front[3];
    QPushButton* sound_rear[3];

private slots:
    void set_time();
    void go_back();
    void front_sound_changed();
    void rear_sound_changed();

signals:
    void homeButtonClicked();
};

#endif // DRIVEASSISTWIDGET_H
