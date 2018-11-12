#include "soundplayer.h"

SoundPlayer::SoundPlayer(QObject *parent) : QObject(parent)
{
    applicationPath = QDir::currentPath(); //get application path
    audioGER_dir.setPath(applicationPath + "/audioGER"); //create directory path of german .wav files
    audioPL_dir.setPath(applicationPath + "/audioPL"); //create directory path of polish .wav files

    playlist_der.addMedia(QUrl::fromLocalFile(audioGER_dir.absolutePath() + "/" + "Der" + ".wav")); //ATTENTION, THIS MAY BE SYSTEM SPECIFIC, if something is wrong append prefix "file:///";)
    playlist_die.addMedia(QUrl::fromLocalFile(audioGER_dir.absolutePath() + "/" + "Die" + ".wav")); //ATTENTION, THIS MAY BE SYSTEM SPECIFIC, if something is wrong append prefix "file:///";)
    playlist_das.addMedia(QUrl::fromLocalFile(audioGER_dir.absolutePath() + "/" + "Das" + ".wav")); //ATTENTION, THIS MAY BE SYSTEM SPECIFIC, if something is wrong append prefix "file:///";)
}

//ATTENTION, PATH CREATION MAY BE SYSTEM SPECIFIC

void SoundPlayer::play_sound(QString word_to_play, QString lang, int article)
{
    qDebug() << "Word to play: " << word_to_play;

    QString soundFilePath;

    //create final sound file path to play
    if(lang == "de")
    {
        soundFilePath = audioGER_dir.absolutePath() + "/" + word_to_play + ".wav"; //ATTENTION, THIS MAY BE SYSTEM SPECIFIC, if something is wrong append prefix "file:///"

        QFileInfo file(soundFilePath);

        qDebug() << soundFilePath;

        if(!file.exists()) //sprawdz czy plik istnieje
        {
            qDebug() << "PLIK KTORY PROBUJESZ ODTWORZYC NIE ISTNIEJE!";
            return;
        }

        if(article!=0) //if it is a noun
        {
            switch(article)
            {
            case 1:
                playlist_der.removeMedia(1); //remove former word
                playlist_der.addMedia(QUrl::fromLocalFile(soundFilePath)); //add new word
                soundToPlay.setPlaylist(&playlist_der); //switch player to playlist
                break;
            case 2:
                playlist_die.removeMedia(1);
                playlist_die.addMedia(QUrl::fromLocalFile(soundFilePath));
                soundToPlay.setPlaylist(&playlist_die);
                break;
            case 3:
                playlist_das.removeMedia(1);
                playlist_das.addMedia(QUrl::fromLocalFile(soundFilePath));
                soundToPlay.setPlaylist(&playlist_das);
                break;
            }
        }
        else
        {
            //set single non-noun audio to play (word without article)
                soundToPlay.setMedia(QMediaContent(QUrl::fromLocalFile(soundFilePath))); //if something is wrong delete "fromLocalFile"
        }
    }
    else if(lang == "pl")
    {
        soundFilePath = audioPL_dir.absolutePath() + "/" + word_to_play + ".wav"; //ATTENTION, THIS MAY BE SYSTEM SPECIFIC, if something is wrong append prefix "file:///"

        QFileInfo file(soundFilePath);

        qDebug() << soundFilePath;

        if(!file.exists()) //sprawdz czy plik istnieje
        {
            qDebug() << "PLIK KTORY PROBUJESZ ODTWORZYC NIE ISTNIEJE!";
            return;
        }

        soundToPlay.setMedia(QMediaContent(QUrl::fromLocalFile(soundFilePath))); //if something is wrong delete "fromLocalFile"
    }

    soundToPlay.play(); //play single sound or playlist
}
