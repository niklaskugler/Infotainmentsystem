#ifndef MULTIMEDIAPLAYER_H
#define MULTIMEDIAPLAYER_H
#include <QObject>
#include <QMediaPlayer>
#include <QPushButton>


class MultimediaPlayer : public QObject
{
    Q_OBJECT

private:
    int volume;
    int channel_nr;
    QString *channel_list;
    QMediaPlayer* player;
    QUrl* channel_link;
    bool player_status;
    QWidget* menu_obj;
    bool mute_state = 0;
    QPushButton *prev_channel;

public:
    explicit MultimediaPlayer(QObject *parent = nullptr);
    ~MultimediaPlayer();
    void channel_selected(QString button_name, QPushButton *button);
    QPushButton* get_prev_channel();
    bool get_player_status();
    void initialize_new_favourite(QString fav_url, QString fav_name);
    int get_channel_nr();
    void set_volume(int volume);
    int get_volume();
    void mute();
    bool get_mute_state();
    void set_channel_nr(int x);
    void stop();
};

#endif // MULTIMEDIAPLAYER_H
