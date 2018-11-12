#include "filesaveload.h"

FileSaveLoad::FileSaveLoad(QObject *parent) : QObject(parent)
{
}

void FileSaveLoad::showWordsVect()
{
    for(Word *item : words_vect)
    {
        (*item).ShowWord();
    }
}

QVector<Word *> FileSaveLoad::getWordsVect()
{
    return words_vect;
}

bool FileSaveLoad::loadWordsFromFile() //return 0 if everything is ok, -1 if file not opened, and some number if there is something wrong with that line
{
    words_vect.clear();
    words_vect.squeeze();

    QString input_file_path = QFileDialog::getOpenFileName(nullptr, tr("Wybierz plik z bazą słówek"), "C:/Users/Adam/Documents", tr("Text files (*.txt)"));

    //qDebug() << "Chosen file is: " << input_file_path;

    QFile input_file(input_file_path);

    if(input_file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Input file opened successfully";
    }
    else
    {
        QMessageBox::warning(nullptr, "Error", "Error! Could not open input file", QMessageBox::Ok);
        return false;
    }

    QTextStream text_input_stream(&input_file);

    //DO NOT DELETE OR IT WILL NOT READ PROPERLY FORMERLY SAVED FILE
    qDebug() << "Codec before is: " << text_input_stream.codec();
    text_input_stream.setCodec("UTF-8");
    qDebug() << "Codec after is: " << text_input_stream.codec();

    QString input_line;

    int lineNumber = 1;

    while(!((input_line = text_input_stream.readLine()).isEmpty()))
    {
        QStringList splitted_words = input_line.split(',');

        if(splitted_words.size() != 5) //if line does not consist of 5 words delimited with commas (wrong formatting)
        {
            QMessageBox::warning(nullptr, "Error, LINE: " + QString::number(lineNumber), "Line does not consist of 5 words delimited with commas", QMessageBox::Ok);
            return false;
        }
        else if(splitted_words.at(0).isEmpty()) //first string is empty (no polish word provided)
        {
            QMessageBox::warning(nullptr, "Error, LINE: " + QString::number(lineNumber), "Polish word is empty", QMessageBox::Ok);
            return false;
        }
        else if(splitted_words.at(2).isEmpty()) //third string is empty (no german word provided)
        {
            QMessageBox::warning(nullptr, "Error, LINE: " + QString::number(lineNumber), "German word is empty", QMessageBox::Ok);
            return false;
        }
        else if(splitted_words.at(4).at(0) != '1' &&
                splitted_words.at(4).at(0) != '2' &&
                splitted_words.at(4).at(0) != '3' &&
                splitted_words.at(4).at(0) != '4') // fifth string is out of 1-4 range
        {
            QMessageBox::warning(nullptr, "Error, LINE: " + QString::number(lineNumber), "Article value is incorrect or out of permitted range (1-4)", QMessageBox::Ok);
            return false;
        }
        else if(splitted_words.at(4).at(0) == '1' && // word is noun, however it has no or wrongly named article
                 splitted_words.at(1) !="der" &&
                 splitted_words.at(1) !="die" &&
                 splitted_words.at(1) !="das")
        {
            qDebug() << "at 4: " << splitted_words.at(4) << "       at 1: " << splitted_words.at(1);
            QMessageBox::warning(nullptr, "Error, LINE: " + QString::number(lineNumber), "Word is noun, however it has no or wrongly named article", QMessageBox::Ok);
            return false;
        }

        Word *word = new Word(splitted_words.at(0), splitted_words.at(1), splitted_words.at(2), splitted_words.at(3), splitted_words.at(4).at(0).toLatin1());
        words_vect.push_back(word);
        qDebug() << "Odczytane slowo to: " << word->word_pol << word->article << word->word_ger << word->plural << word->type;

        lineNumber++;
    }

    input_file.close();

    return true;
}

bool FileSaveLoad::saveFile(const QVector<Word*> & _wordvect)
{
    QString save_file_path = QFileDialog::getSaveFileName(nullptr, "Wskaż miejsce zapisu bazy słówek", "C:/Users/Adam/Documents", tr("Text files (*.txt)"));

    QFile output_file(save_file_path);

    if(output_file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Output file opened successfully";
    }
    else
    {
        qDebug() << "ERROR! Could not open output file";
        return false;
    }

    qDebug() << "Rozmiar wektora PO uruchomieniu w funkcji" << _wordvect.size();

    QTextStream text_output_stream(&output_file);

    qDebug() << "Codec before is: " << text_output_stream.codec();
    text_output_stream.setCodec("UTF-8");
    qDebug() << "Codec after is: " << text_output_stream.codec();

    for(int i=0; i<_wordvect.size(); i++)
    {
        text_output_stream << _wordvect.at(i)->full_line;
    }

    output_file.close();

    return true;
}
