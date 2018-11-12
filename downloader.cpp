#include "downloader.h"

Downloader::Downloader(QString _word_to_sound, QString _lang, QObject *parent) : QObject(parent)
{
    word_to_sound = _word_to_sound;
    lang = _lang;
}

void Downloader::Do_Download()
{
    networkaccess_manager = new QNetworkAccessManager(this);

    connect(networkaccess_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    QUrl address("http://translate.google.com.vn/translate_tts?ie=UTF-8&q=" + word_to_sound + "+&tl=" + lang + "&client=tw-ob");

    QNetworkReply *replyblet = networkaccess_manager->get(QNetworkRequest(QUrl(address)));
}

void Downloader::replyFinished(QNetworkReply *reply)
{
    //qDebug() << "REPLY FINISHED dla " << word_to_sound;

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        QString application_path = QDir::currentPath();
        QDir application_dir(application_path);
        QDir audioGER_dir(application_path + "/audioGER");
        QDir audioPL_dir(application_path + "/audioPL");

        if(!audioGER_dir.exists())
        {
            application_dir.mkdir("audioGER");
            qDebug() << "Directory audio GER created";
        }

        if(!audioPL_dir.exists())
        {
            application_dir.mkdir("audioPL");
            qDebug() << "Directory audio PL created";
        }

        QFile *file = nullptr;

        if(lang == "de")
        {
            file = new QFile(audioGER_dir.absolutePath() + "/" + word_to_sound + ".wav");
        }
        else if(lang == "pl")
        {
            file = new QFile(audioPL_dir.absolutePath() + "/" + word_to_sound + ".wav");
        }

        if(file->exists())
        {
            //qDebug("FILE ALREADY EXISTS, NOTHING DOWNLOADED");
            delete file;
            reply->deleteLater();
            return;
        }

        if(file->open(QFile::WriteOnly | QFile::Truncate))
        {
            qDebug("DOWNLOADING FILE");

            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;
    }

    reply->deleteLater();

    //possible memory leak
    this->deleteLater();
}
