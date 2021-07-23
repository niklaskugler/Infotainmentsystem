#include "mediaPlayer.h"

#include "gui/mediaPlayerWidget.h"

MediaPlayer::MediaPlayer(MediaPlayerWidget* parent, QObject *_parent) : QObject(_parent)
{
    player = new QMediaPlayer;

    media_player_gui = parent;

    volume = 50;    //initialisierung mit 50

    player_status = 0;   //player spielt nicht

    mute_state = 0; //player spielt zu beginn nicht

    playlist_index = 0;
    //Playlist initialisieren
    playlist[0] = "qrc:/Music/Adel Tawil - Lieder.mp3";
    playlist[1] = "qrc:/Music/Bastille - Pompeii.mp3";
    playlist[2] = "qrc:/Music/OneRepublic - Counting Stars.mp3";

    player->setMedia(playlist[0]);

    QObject::connect(player, &QMediaPlayer::positionChanged, this, &MediaPlayer::change_position);
    QObject::connect(player, &QMediaPlayer::durationChanged, this, &MediaPlayer::change_duration);
}

MediaPlayer::~MediaPlayer()
{
    delete player;
}

void MediaPlayer::set_volume(int volume)
{
    this->volume = volume;
    if(mute_state == 0)
    {
        player->setVolume(volume);
    }
}

void MediaPlayer::mute()
{
    if(mute_state == 0)
    {
        mute_state = 1;
        player->setVolume(0);
    }
    else
    {
        mute_state = 0;
        player->setVolume(volume);
    }
}

int MediaPlayer::get_volume()
{
    return volume;
}

bool MediaPlayer::get_mute_state()
{
    return mute_state;
}

bool MediaPlayer::get_player_status()
{
    return player_status;
}

void MediaPlayer::play()
{
    if(player_status == 0)   //player spielt nicht
    {
        player->play();
        player_status = 1;
    }
    else
    {
        player->pause();
        player_status = 0;
    }
}
int MediaPlayer::next()
{
    playlist_index += 1;
    player->setMedia(playlist[playlist_index%3]);
    player->play();

    return playlist_index;
}
int MediaPlayer::back()
{
    playlist_index -= 1;
    if(playlist_index == -1)
        playlist_index = 2;
    player->setMedia(playlist[playlist_index%3]);
    player->play();

    return playlist_index;
}

void MediaPlayer::change_time(int time)
{
    player->setPosition(time);
}

void MediaPlayer::change_position(qint64 position)
{
    media_player_gui->change_position(position);
}

void MediaPlayer::change_duration(qint64 position)
{
    media_player_gui->change_duration(position);
}
