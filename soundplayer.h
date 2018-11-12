#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>

class SoundPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SoundPlayer(QObject *parent = nullptr);
    void play_sound(QString word_to_play, QString lang, int article); //ATTENTION, PATH CREATION MAY BE SYSTEM SPECIFIC
private:
    QMediaPlayer soundToPlay;

    QMediaPlaylist playlist_der;
    QMediaPlaylist playlist_die;
    QMediaPlaylist playlist_das;

    QString applicationPath;
    QDir audioGER_dir;
    QDir audioPL_dir;

signals:

public slots:
};

#endif // SOUNDPLAYER_H
