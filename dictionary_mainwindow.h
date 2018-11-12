#ifndef DICTIONARY_MAINWINDOW_H
#define DICTIONARY_MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QStandardItemModel>
#include "word.h"
#include "filesaveload.h"
#include "soundplayer.h"
#include "testmode.h"

namespace Ui {
class Dictionary_MainWindow;
}

class Dictionary_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dictionary_MainWindow(QWidget *parent = 0);
    void InitializeTable();
    void updateTable();

    ~Dictionary_MainWindow();

    void hideAllTableRows();

public slots:
    void play_sound(QModelIndex index);

private slots:
    void on_actionAdd_word_triggered();

    void on_actionRemove_word_triggered();

    void on_actionZapiszSlowaWPliku_triggered();

    void on_actionSortuj_kolumna_1_triggered();
    void on_actionSortuj_kolumna_2_triggered();
    void on_actionSortuj_kolumna_3_triggered();

    void on_lineEdit_FindItem_textChanged(const QString &arg1);

    void on_actionQuit_triggered();

    void on_actionTestMode_triggered();

    void on_actionEdit_word_triggered();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Dictionary_MainWindow *ui;
    QStandardItemModel *tableModel;
    QVector<Word*> words_vect;
    SoundPlayer *soundplayer;
    TestMode *testmode;
    QKeyEvent *key_event;
    int modelSortingColumn;
};

#endif // DICTIONARY_MAINWINDOW_H
