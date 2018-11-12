#include "word.h"

Word::Word(QString _word_pol, QString _article, QString _word_ger,  QString _plural, char _type, QObject *parent) : QObject(parent)
{
    word_pol = _word_pol;
    article = _article;
    word_ger = _word_ger;
    plural = _plural;
    type = _type; // 0 = other, 1 = noun, 2 = verb, 3 = adjective

    full_line = word_pol + "," + article + "," + word_ger + "," + plural + "," + QString(type) + "\n"; //line used when saving words to file

    DownloadWordAudioPL();
    DownloadWordAudioGER();
    DownloadWordAudioGER_Plural();
}

void Word::ShowWord()
{
    qDebug().noquote() << word_pol << word_ger;
}

void Word::DownloadWordAudioPL()
{
    Downloader *downloader = new Downloader(word_pol, "pl"); // download polish word audio
    downloader->Do_Download();
}

void Word::DownloadWordAudioGER()
{
    Downloader *downloader = new Downloader(word_ger, "de"); // download german word audio
    downloader->Do_Download();
}

void Word::DownloadWordAudioGER_Plural()
{
    if(!plural.isEmpty())
    {
        Downloader *downloader = new Downloader(plural, "de"); // download german word audio plural
        downloader->Do_Download();
    }
}
