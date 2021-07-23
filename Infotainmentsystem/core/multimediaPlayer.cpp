#include "multimediaPlayer.h"

MultimediaPlayer::MultimediaPlayer(QObject *parent) : QObject(parent)
{
    channel_nr = 5;     //zu Beginn 5 Favoritenchannel

    volume = 50;    //initialisierung mit 50

    player_status = 0;   //player spielt nicht

    prev_channel = nullptr;

    channel_list = new QString[channel_nr];
    channel_link = new QUrl[channel_nr];

    channel_list[0] = "FFH";
    channel_list[1] = "SWR3";
    channel_list[2] = "SWR1";
    channel_list[3] = "Bayern3";
    channel_list[4] = "HR3";

    channel_link[0] = "http://mp3.ffh.de/radioffh/hqlivestream.mp3";
    channel_link[1] = "http://swr-edge-3025-dus-ts-cdn.cast.addradio.de/swr/swr3/live/mp3/128/stream.mp3?_art=dj0yJmlwPTE0MS4zNy4yMDAuMTImaWQ9aWNzY3hsLWJ6c2UzMmxsYiZ0PTE2MTg1OTEyNjMmcz03ODY2ZjI5YyM3NTExNGVmNjFlMDNiMmI2ZTNkN2U1MmMyMTgwNTQwZQ";
    channel_link[2] = "http://swr-edge-3022-dus-ts-cdn.cast.addradio.de/swr/swr1/bw/mp3/128/stream.mp3?_art=dj0yJmlwPTE0MS4zNy4yMDAuMTImaWQ9aWNzY3hsLXF4c2UzMmxsYiZ0PTE2MTg1OTEyODYmcz03ODY2ZjI5YyMyMzc0ODk5YzQyYThjMzUyZGFiYjhmOTFlMzJhYjg5Ng";
    channel_link[3] = "http://br-edge-3006-fra-ts-cdn.cast.addradio.de/br/br3/live/mp3/128/stream.mp3?_art=dj0yJmlwPTE0MS4zNy4yMDAuMTImaWQ9aWNzY3hsLWRzcWR4d2tsYiZ0PTE2MTg1OTExNzcmcz03ODY2ZjI5YyM5NGZmMjZlODg5MjczMzIwN2Q2YmMxODM0NjRlNzE1MA";
    channel_link[4] = "http://hr-edge-3048-dus-ts-cdn.cast.addradio.de/hr/hr3/live/mp3/128/stream.mp3?_art=dj0yJmlwPTE0MS4zNy4yMDAuMTImaWQ9aWNzY3hsLWYzb2p4amxsYiZ0PTE2MTg1OTEyMDMmcz03ODY2ZjI5YyMzMmE3OGUxODUxMzMwNDZjZjAxMDAzZmJlYjM5ZWI1Yw";

    player = new QMediaPlayer;

    mute_state = 0;
}

MultimediaPlayer::~MultimediaPlayer()
{
    delete [] channel_list;
    delete [] channel_link;
    delete player;
}

void MultimediaPlayer::channel_selected(QString button_name, QPushButton *button)
{
    if(prev_channel == button && player_status == 1)
    {
        player->stop();
        player_status = 0;
        return;
    }

    player_status = 1;
    prev_channel = button;

    for(int i = 0; i < channel_nr;i++)
    {

        if (button_name == "Button" + QString::number(i+1))
        {
                qInfo() << "Channel: " << channel_list[i] << "selected";
                player->setMedia(channel_link[i]);     //MP3 Stream muss angegeben werden

        }
    }

    if(mute_state == 1)
        player->setVolume(0);
    else
        player->setVolume(volume);

    player->play();

    return;
}

QPushButton* MultimediaPlayer::get_prev_channel()
{
    return prev_channel;
}

bool MultimediaPlayer::get_player_status()
{
    return player_status;
}

int MultimediaPlayer::get_channel_nr()
{
    return channel_nr;
}

int MultimediaPlayer::get_volume()
{
    return volume;
}

bool MultimediaPlayer::get_mute_state()
{
    return mute_state;
}

void MultimediaPlayer::set_channel_nr(int x)
{
    channel_nr = x;
}

void MultimediaPlayer::initialize_new_favourite(QString fav_url, QString fav_name)
{

    channel_nr += 1;

    QString* ptemp1 = new QString[channel_nr];                  //neue vergrößerte arrays anlegen
    QUrl* ptemp2 = new QUrl[channel_nr];

    for(int i = 0; i<channel_nr-1;i++)  //kopieren der alten array werte in die neuen arrays
    {
        ptemp1[i] = channel_list[i];
        ptemp2[i] = channel_link[i];
    }

    //löschen der alten arrays
    delete [] channel_list;
    delete [] channel_link;

    channel_list = ptemp1;
    channel_link = ptemp2;

    channel_link[channel_nr-1] = QUrl(fav_url);       //übertragung der neuen Werte
    channel_list[channel_nr-1] = fav_name;
}

void MultimediaPlayer::set_volume(int volume)
{
    this->volume = volume;
    if(mute_state == 0)
    {
        player->setVolume(volume);
    }
}

void MultimediaPlayer::mute()
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

void MultimediaPlayer::stop()
{
    player->stop();
    player_status = 0;
}
