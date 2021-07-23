#ifndef MEDIAPLAYERWIDGET_H
#define MEDIAPLAYERWIDGET_H

#include "core/mediaPlayer.h"
#include <QWidget>

class InfotainmentsystemWindow;
class QPushButton;
class QTimer;
class QMediaPlayer;
class QSlider;

namespace Ui {
class MediaPlayerWidget;
}

class MediaPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaPlayerWidget(InfotainmentsystemWindow *menu, QWidget *parent = nullptr);
    ~MediaPlayerWidget();
    void stop_Player();
    void change_time();
    void change_position(qint64 position);
    void change_duration(qint64 position);

private:
    Ui::MediaPlayerWidget *ui;
    QPushButton *side_menu[5];
    InfotainmentsystemWindow* infotainmentsystem_obj;
    QTimer *timer;
    QWidget* menu_obj;
    QPushButton* HomeButton;
    QPushButton* mute_button;
    QSlider *volume_adjuster;
    QSlider *progress_slider;
    MediaPlayer* mediaplayer_logic;
    QPushButton* control_buttons[3];
    QString song_cover_img[3];
    int current_max;
    QString song_title[3];

private slots:
    void go_home();
    void set_time();
    void side_menu_clicked();
    void set_volume();
    void mute();
    void control_button_clicked();

signals:
    void homeButtonClicked();
};

#endif // MEDIAPLAYERWIDGET_H
