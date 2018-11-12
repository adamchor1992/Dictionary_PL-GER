#include "testmode.h"
#include "ui_testmodewindow.h"

TestMode::TestMode(QVector<Word *> _words_vect, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestMode)
{
    ui->setupUi(this);

    this->setWindowTitle("Test");

    words_vect = _words_vect;

    qDebug() << "W przekazanym wektorze jest " << words_vect.size() << " slow";

    questions_count = 10;

    qDebug() << "Wygenerowanych losowo" << questions_count << "slow to: ";

    QVector<Word *> random_words = SelectRandomWords(questions_count);

    for(Word *Item : random_words)
    {
        qDebug().noquote() << Item->word_ger << Item->word_pol << Item->type;
    }

    InitializeTable(random_words);

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(CheckAnswer(int)));

    correct_answers = 0;
    total_answers = 0;

    connect(this, SIGNAL(SendAnswer(bool)), this, SLOT(CountAnswers(bool)));
}

void TestMode::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}

QVector<Word *> TestMode::SelectRandomWords(int number_of_words)
{
    QRandomGenerator *generator = QRandomGenerator::system();

    QSet<quint32> randomnumbers_set;

    while(randomnumbers_set.size() < number_of_words)
    {
        randomnumbers_set.insert(generator->bounded(0, words_vect.size()-1));
    }

    QVector<Word *> random_words;

    for(auto item : randomnumbers_set)
    {
        random_words.push_back(words_vect.at(item));
    }

    return random_words;
}

void TestMode::InitializeTable(QVector<Word *> random_words)
{
    ui->tableWidget->setRowCount(random_words.size());

    for(int i=0; i < random_words.size() ; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(random_words.at(i)->word_pol));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(random_words.at(i)->word_ger));
    }

    ui->tableWidget->hideColumn(1);
}

void TestMode::CheckAnswer(int row)
{
    QString answer = ui->tableWidget->item(row, 2)->text();

    if(answer.isEmpty())
    {
        return; //nothing entered
    }

    QString polish_word = ui->tableWidget->item(row, 0)->text();
    QString english_word = ui->tableWidget->item(row,1)->text();

    if(answer == english_word)
    {
        QMessageBox::information(this, "Info", "Dobra odpowiedź, \"" + polish_word + "\" to po angielsku \"" + english_word + "\"", QMessageBox::Ok);
        qDebug() << "DOBRA ODPOWIEDŹ";
        emit SendAnswer(true);
    }
    else
    {
        QMessageBox::warning(this, "Info", "Zła odpowiedź!, \"" + polish_word + "\" to po angielsku \"" + english_word + "\"", QMessageBox::Ok);
        qDebug() << "ZŁA ODPOWIEDŹ" << "prawidłowa to: " << english_word;
        emit SendAnswer(false);
    }

    ui->tableWidget->removeRow(row);
}

void TestMode::CountAnswers(bool grade)
{
    if(grade == true)
    {
        correct_answers++;
        total_answers++;
    }
    else
    {
        total_answers++;
    }

    if(total_answers == questions_count)
    {
        QMessageBox::information(this, "Ocena", "Ocena końcowa: " + QString::number(correct_answers) + " na " + QString::number(total_answers), QMessageBox::Ok);
        parentWidget()->show();
        close();
    }
}

TestMode::~TestMode()
{
    qDebug() << "TEST MODE DESTRUCTED";
    delete ui;
}
