#ifndef WORD_H
#define WORD_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <downloader.h>

class Word : public QObject
{
    Q_OBJECT
public:
    explicit Word(QString _word_pol = 0, QString _article = 0, QString _word_ger = 0, QString _plural = 0, char _type = 0, QObject *parent = nullptr);
    void ShowWord();
    void DownloadWordAudioPL();
    void DownloadWordAudioGER();
    void DownloadWordAudioGER_Plural();

    QString word_pol;
    QString article;
    QString word_ger;
    QString plural;
    char type; // 0 = other, 1 = noun, 2 = verb, 3 = adjective



    QString full_line; //convenience line for saving words in file

signals:

public slots:
};

#endif // WORD_H
