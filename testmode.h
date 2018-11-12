#ifndef TESTMODE_H
#define TESTMODE_H

#include <QMainWindow>
#include <QDebug>
#include <QRandomGenerator>
#include <QMessageBox>
#include <word.h>

namespace Ui {
class TestMode;
}

class TestMode : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestMode(QVector<Word*> _words_vect, QWidget *parent = 0);

    void closeEvent(QCloseEvent *event);

    QVector<Word*> SelectRandomWords(int number_of_words);
    void InitializeTable(QVector<Word *> random_words);

    ~TestMode();

signals:
    void SendAnswer(bool grade); //true is correct, false is wrong answer

public slots:
    void CheckAnswer(int row);
    void CountAnswers(bool grade);

private:
    Ui::TestMode *ui;
    QVector<Word*> words_vect;
    int questions_count;
    int correct_answers;
    int total_answers;
};

#endif // TESTMODE_H
