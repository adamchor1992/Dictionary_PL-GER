#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QString _word_to_sound, QString lang, QObject *parent = 0);
    void Do_Download();

signals:

public slots:
    void replyFinished (QNetworkReply *reply);

private:
    QNetworkAccessManager *networkaccess_manager;
    QString word_to_sound;
    QString lang;
};

#endif // DOWNLOADER_H
