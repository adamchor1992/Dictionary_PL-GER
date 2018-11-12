#ifndef FILESAVELOAD_H
#define FILESAVELOAD_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <word.h>

class FileSaveLoad : public QObject
{
    Q_OBJECT
public:
    explicit FileSaveLoad(QObject *parent = nullptr);
    bool loadWordsFromFile();
    bool saveFile(const QVector<Word *> & _wordvect);
    void showWordsVect();

    QVector<Word*> getWordsVect();

private:
    QVector<Word*> words_vect; //vector storing pointers to Word objects

signals:

public slots:
};

#endif // FILESAVELOAD_H
