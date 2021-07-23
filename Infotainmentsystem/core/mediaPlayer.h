#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QMediaPlayer>
#include <QUrl>

class MediaPlayerWidget;

class MediaPlayer : public QObject
{
    Q_OBJECT

public:
    explicit MediaPlayer(MediaPlayerWidget *parent, QObject *_parent = nullptr);
    ~MediaPlayer();
    void set_volume(int volume);
    int get_volume();
    void mute();
    bool get_mute_state();
    bool get_player_status();
    void play();
    int next();
    int back();
    void change_time(int time);
    void change_position(qint64 position);
    void change_duration(qint64 position);

private:
    int volume;
    bool mute_state;
    bool player_status;
    QMediaPlayer* player;
    QUrl playlist[3];
    int playlist_index;
    MediaPlayerWidget* media_player_gui;
};

#endif // MEDIA_PLAYER_H
