#ifndef MultimediaPlayerWidget_H
#define MultimediaPlayerWidget_H

class QPushButton;
class QMediaPlayer;
class QTimer;
class QSlider;
class QToolButton;

#include "gui/addNewFavouriteWidget.h"
#include "gui/confirmFavDeletionWidget.h"

#include "core/multimediaPlayer.h"

class InfotainmentsystemWindow;        //forward declaration of class InfotainmentsystemWindow since cross includes are not allowed

QT_BEGIN_NAMESPACE
namespace Ui { class MultimediaPlayerWidget; }
QT_END_NAMESPACE

class MultimediaPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    MultimediaPlayerWidget(InfotainmentsystemWindow *menu, QWidget *parent = nullptr);
    ~MultimediaPlayerWidget();
    int get_channel_nr();
    void delete_favs_confirmed();
    void stop_Player();

private:
    Ui::MultimediaPlayerWidget *ui;
    QPushButton **channel_buttons;
    QPushButton * mute_button;
    QToolButton* addfav;
    AddNewFavouriteWidget *popupwindow;
    ConfirmFavDeletionWidget *popupwindow2;
    QPushButton* HomeButton;
    QWidget* menu_obj;
    QTimer *timer_radio;
    QSlider *volume_adjuster;
    QPushButton* DeleteButton;
    MultimediaPlayer* mediaplayer_logic;
    QPushButton *side_menu[5];
    InfotainmentsystemWindow* infotainmentsystem_obj;

private slots:
    void channel_selected();
    void add_favourite();
    void initialize_new_favourite();
    void go_home();
    void set_time();
    void set_volume();
    void mute();
    void delete_favs();
    void side_menu_clicked();

signals:
    void homeButtonClicked();

};
#endif // MultimediaPlayerWidget_H
