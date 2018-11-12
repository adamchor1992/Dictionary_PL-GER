#include "dictionary_mainwindow.h"
#include "ui_dictionary_mainwindow.h"
#include "addworddialog.h"
#include "ui_addword_dialog.h"
#include "editworddialog.h"

Dictionary_MainWindow::Dictionary_MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::Dictionary_MainWindow)
{
    ui->setupUi(this);

    soundplayer = new SoundPlayer(this);

    FileSaveLoad filesaveload;

    while(!filesaveload.loadWordsFromFile())
    {
        if(QMessageBox::question(this, "Error", "Choose another file", QMessageBox::Ok, QMessageBox::Abort) == QMessageBox::Abort) //if abort clicked
        {
            exit(1);
        }
    }

    words_vect = filesaveload.getWordsVect();

    tableModel = new QStandardItemModel;

    modelSortingColumn = 0; //sort by 0 column (first column)

    InitializeTable();

    this->setFocus();
}

void Dictionary_MainWindow::InitializeTable()
{
    int word_count = words_vect.size();

    qDebug() << "WORD COUNT = " << word_count;

    QList<QStandardItem*> wordRow_ptr; //5 elements list of pointers to items created on heap, initialized with nullptr
    wordRow_ptr.append(nullptr);
    wordRow_ptr.append(nullptr);
    wordRow_ptr.append(nullptr);
    wordRow_ptr.append(nullptr);
    wordRow_ptr.append(nullptr);

    tableModel->sort(0); //sort by first column

    for(int i = 0; i < word_count; i++) //i for rows
    {
        QStandardItem *itemColumn1 = new QStandardItem(words_vect.at(i)->word_pol);
        QStandardItem *itemColumn2 = new QStandardItem(words_vect.at(i)->article);
        QStandardItem *itemColumn3 = new QStandardItem(words_vect.at(i)->word_ger);
        QStandardItem *itemColumn4 = new QStandardItem(words_vect.at(i)->plural);

        QStandardItem *itemColumn5;

        if(words_vect.at(i)->type == '0')
        {
            itemColumn5 = new QStandardItem("Nie podano");
        }
        else if(words_vect.at(i)->type == '1')
        {
            itemColumn5 = new QStandardItem("RZECZ");
        }
        else if(words_vect.at(i)->type == '2')
        {
            itemColumn5 = new QStandardItem("CZAS");
        }
        else if(words_vect.at(i)->type == '3')
        {
            itemColumn5 = new QStandardItem("PRZYM");
        }
        else if(words_vect.at(i)->type == '4')
        {
            itemColumn5 = new QStandardItem("WYRAŻ");
        }
        else
        {
            itemColumn5 = new QStandardItem("BŁĄD");
        }

        //reset flags and set item as NON-EDITABLE
        itemColumn1->setFlags(nullptr);
        itemColumn2->setFlags(nullptr);
        itemColumn3->setFlags(nullptr);
        itemColumn4->setFlags(nullptr);
        itemColumn5->setFlags(nullptr);
        itemColumn1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn3->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn4->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn5->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        if(i%2==0)
        {
            itemColumn1->setBackground(QColor(197,246,255));
            itemColumn2->setBackground(QColor(197,246,255));
            itemColumn3->setBackground(QColor(197,246,255));
            itemColumn4->setBackground(QColor(197,246,255));
            itemColumn5->setBackground(QColor(197,246,255));
        }

        //populate list with item pointers
        wordRow_ptr[0] = itemColumn1;
        wordRow_ptr[1] = itemColumn2;
        wordRow_ptr[2] = itemColumn3;
        wordRow_ptr[3] = itemColumn4;
        wordRow_ptr[4] = itemColumn5;

        tableModel->appendRow(wordRow_ptr);
    }

    //ALTERNATIVE IMPLEMENTATION USING INDEX
//    for(int i  =0; i < word_count; i++) //i for rows
//    {
//        for(int j = 0; j<5; j++) //j for columns
//        {
//            index = tableModel->index(i,j);

//            switch(j)
//            {
//            case 0:
//                tableModel->setData(index, QString(words_vect.at(i)->word_pol));
//                break;
//            case 1:
//                tableModel->setData(index, QString(words_vect.at(i)->article));
//                break;
//            case 2:
//                tableModel->setData(index, QString(words_vect.at(i)->word_ger));
//                break;
//            case 3:
//                tableModel->setData(index, QString(words_vect.at(i)->plural));
//                break;
//            case 4:
//                if(words_vect.at(i)->type == '0')
//                {
//                    tableModel->setData(index, QString("Nie podano"));
//                }
//                else if(words_vect.at(i)->type == '1')
//                {
//                    tableModel->setData(index, QString("RZECZ."));
//                }
//                else if(words_vect.at(i)->type == '2')
//                {
//                    tableModel->setData(index, QString("CZAS."));
//                }
//                else if(words_vect.at(i)->type == '3')
//                {
//                    tableModel->setData(index, QString("PRZYM."));
//                }
//                else if(words_vect.at(i)->type == '4')
//                {
//                    tableModel->setData(index, QString("WYRAŻ."));
//                }
//                else
//                {
//                    tableModel->setData(index, QString("BŁĄD"));
//                }
//                tableModel->setData(index, QString(words_vect.at(i)->word_pol));
//                break;
//            }
//        }
//    }

    ui->tableView->setModel(tableModel);
    ui->tableView->resizeColumnsToContents();

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex)), this, SLOT(play_sound(QModelIndex)));
}

void Dictionary_MainWindow::updateTable()
{
    //sort by column 1 + update table items' background colours

    tableModel->sort(modelSortingColumn);

    int rowCount = tableModel->rowCount();
    int columnCount = tableModel->columnCount();

    QStandardItem *item;

    for(int i = 0; i < rowCount; i++)
    {
        for(int j = 0; j < columnCount; j++)
        {
            item = tableModel->item(i,j);
            if(i%2==0)
            {
                item->setBackground(QColor(197,246,255));
            }
            else
            {
                item->setBackground(QColor(255,255,255));
            }
        }
    }
}

void Dictionary_MainWindow::play_sound(QModelIndex index)
{
    qDebug() << "Wiersz: " << index.row() + 1  << "Kolumna: " << index.column() + 1;
    qDebug() << "Word is: " << tableModel->data(index).toString(); //get data under index in table model

    int article = 0; //0 for no article, 1 for der, 2 for die, 3 for das

    if(index.column() == 0)
    {
        if(tableModel->item(index.row(),4)->text() == "RZECZ")
        {
            if(tableModel->item(index.row(),1)->text() == "der")
            {
                qDebug() << "RODZAJNIK DER";
                article = 1;
            }
            else if(tableModel->item(index.row(),1)->text() == "die")
            {
                qDebug() << "RODZAJNIK DIE";
                article = 2;
            }
            else if(tableModel->item(index.row(),1)->text() == "das")
            {
                qDebug() << "RODZAJNIK DAS";
                article = 3;
            }
        }

        soundplayer->play_sound(tableModel->data(index).toString(), "pl", article);
    }
    else if(index.column() == 2)
    {
        if(tableModel->item(index.row(),4)->text() == "RZECZ")
        {
            if(tableModel->item(index.row(),1)->text() == "der")
            {
                qDebug() << "RODZAJNIK DER";
                article = 1;
            }
            else if(tableModel->item(index.row(),1)->text() == "die")
            {
                qDebug() << "RODZAJNIK DIE";
                article = 2;
            }
            else if(tableModel->item(index.row(),1)->text() == "das")
            {
                qDebug() << "RODZAJNIK DAS";
                article = 3;
            }
        }

        soundplayer->play_sound(tableModel->data(index).toString(), "de", article);
    }
    else if(index.column() == 3)
    {
        if(tableModel->item(index.row(),4)->text() == "RZECZ")
        {
            if(tableModel->item(index.row(),1)->text() == "der")
            {
                qDebug() << "RODZAJNIK DER";
                article = 1;
            }
            else if(tableModel->item(index.row(),1)->text() == "die")
            {
                qDebug() << "RODZAJNIK DIE";
                article = 2;
            }
            else if(tableModel->item(index.row(),1)->text() == "das")
            {
                qDebug() << "RODZAJNIK DAS";
                article = 3;
            }
        }

        soundplayer->play_sound(tableModel->data(index).toString(), "de", article);
    }
}

void Dictionary_MainWindow::on_actionAdd_word_triggered()
{
    this->hide(); //hide main window

    AddWordDialog addword_dialog(this);
    addword_dialog.show();
    int status = addword_dialog.exec();

    qDebug() << "Status dialogu: " << status;

    if(status == QDialog::Accepted)
    {
        qDebug() << "Dialog OK";
        qDebug() << "Dialog zwrocil slowa: " << addword_dialog.getWord_To_Add_PL() << addword_dialog.getWord_To_Add_Article() << addword_dialog.getWord_To_Add_GER() << addword_dialog.getWord_To_Add_Plural() << addword_dialog.getWordType();

        Word *word = new Word(QString(addword_dialog.getWord_To_Add_PL()), QString(addword_dialog.getWord_To_Add_Article()), QString(addword_dialog.getWord_To_Add_GER()), QString(addword_dialog.getWord_To_Add_Plural()), addword_dialog.getWordType());

        words_vect.push_back(word); //add word to main word database (vector)

        QStandardItem *itemColumn1 = new QStandardItem(word->word_pol);
        QStandardItem *itemColumn2 = new QStandardItem(word->article);
        QStandardItem *itemColumn3 = new QStandardItem(word->word_ger);
        QStandardItem *itemColumn4 = new QStandardItem(word->plural);

        QStandardItem *itemColumn5;


        if(word->type == '0')
        {
            itemColumn5 = new QStandardItem("Nie podano");
        }
        else if(word->type == '1')
        {
            itemColumn5 = new QStandardItem("RZECZ");
        }
        else if(word->type == '2')
        {
            itemColumn5 = new QStandardItem("CZAS");
        }
        else if(word->type == '3')
        {
            itemColumn5 = new QStandardItem("PRZYM");
        }
        else if(word->type == '4')
        {
            itemColumn5 = new QStandardItem("WYRAŻ");
        }
        else
        {
            itemColumn5 = new QStandardItem("BŁĄD");
        }

        //reset flags and set item as NON-EDITABLE
        itemColumn1->setFlags(nullptr);
        itemColumn2->setFlags(nullptr);
        itemColumn3->setFlags(nullptr);
        itemColumn4->setFlags(nullptr);
        itemColumn5->setFlags(nullptr);
        itemColumn1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn3->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn4->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemColumn5->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        //5 elements list of pointers to items created on heap, initialized with nullptr
        QList<QStandardItem*> wordRow_ptr;
        wordRow_ptr.append(nullptr);
        wordRow_ptr.append(nullptr);
        wordRow_ptr.append(nullptr);
        wordRow_ptr.append(nullptr);
        wordRow_ptr.append(nullptr);

        //populate list with item pointers
        wordRow_ptr[0] = itemColumn1;
        wordRow_ptr[1] = itemColumn2;
        wordRow_ptr[2] = itemColumn3;
        wordRow_ptr[3] = itemColumn4;
        wordRow_ptr[4] = itemColumn5;

        tableModel->appendRow(wordRow_ptr);

        qDebug() << "Dopisane slowo po polsku i angielsku to: " << word->word_pol << word->article << word->word_ger << word->plural << word->type;

        updateTable();
    }
    else
    {
        qDebug() << "Dialog CANCEL";
    }

    this->show(); //show main window again
}

void Dictionary_MainWindow::on_actionEdit_word_triggered()
{
    QMessageBox::information(this, "BRAK IMPLEMENTACJI", "Jeszcze nie zaimplementowano ;-)");
//    if(ui->tableWidget->selectedItems().size() >= 1)
//    {
//        qDebug() << "Selected items row: " << ui->tableWidget->selectedItems().at(0)->row();
//    }
//    int selected_row = ui->tableWidget->selectedItems().at(0)->row();

//    QVector<QString> itemsinrow_vect;
//    itemsinrow_vect.push_back(ui->tableWidget->item(selected_row, 0)->text());
//    itemsinrow_vect.push_back(ui->tableWidget->item(selected_row, 1)->text());
//    itemsinrow_vect.push_back(ui->tableWidget->item(selected_row, 2)->text());
//    itemsinrow_vect.push_back(ui->tableWidget->item(selected_row, 3)->text());
//    itemsinrow_vect.push_back(ui->tableWidget->item(selected_row, 4)->text());

//    EditWordDialog editword_dialog(itemsinrow_vect);
//    editword_dialog.show();
//    int status = editword_dialog.exec();

//    qDebug() << "Dialog edycji slowa zwrocil slowa: " << editword_dialog.getWord_To_Add_PL() << editword_dialog.getWord_To_Add_Article() << editword_dialog.getWord_To_Add_GER() << editword_dialog.getWord_To_Add_Plural() << editword_dialog.getWordType();

//    if(status == QDialog::Accepted)
//    {
//        qDebug() << "Dialog OK";

//        Word *word = new Word(QString(editword_dialog.getWord_To_Add_PL()), QString(editword_dialog.getWord_To_Add_Article()), QString(editword_dialog.getWord_To_Add_GER()), QString(editword_dialog.getWord_To_Add_Plural()), editword_dialog.getWordType());
//        words_vect.push_back(word);
//        qDebug() << "Dopisane slowo po polsku i angielsku to: " << word->word_pol << word->article << word->word_ger << word->plural << word->type;
//        UpdateTable(word);
//    }
//    else
//    {
//        qDebug() << "Dialog CANCEL";
//    }
}

void Dictionary_MainWindow::on_actionRemove_word_triggered()
{
    QModelIndex index = ui->tableView->currentIndex();

    QList<QStandardItem*> pointersToDelete = tableModel->takeRow(index.row()); //take pointers of row items to delete them

    qDebug() << "Rozmiar pointerstodelete" << pointersToDelete.size();

    for(auto item_ptr : pointersToDelete)
    {
        delete item_ptr; //very important item deletion
    }

    updateTable();
}

void Dictionary_MainWindow::on_actionZapiszSlowaWPliku_triggered()
{
    FileSaveLoad filesaveload;

    words_vect.clear();
    words_vect.squeeze();

    qDebug() << "Rozmiar wektora przed uruchomieniem funkcji zapisu do pliku" << words_vect.size();
    qDebug() << "Liczba slowek w modelu: " << tableModel->rowCount();

    for(int i=0; i < tableModel->rowCount(); i++)
    {
        QStandardItem *itemColumn1 = tableModel->item(i, 0);
        QStandardItem *itemColumn2 = tableModel->item(i, 1);
        QStandardItem *itemColumn3 = tableModel->item(i, 2);
        QStandardItem *itemColumn4 = tableModel->item(i, 3);
        QStandardItem *itemColumn5 = tableModel->item(i, 4);

        char type;

        switch(itemColumn5->text().at(0).toLatin1())
        {
        case 'R':
            type = '1';
            break;
        case 'C':
            type = '2';
            break;
        case 'P':
            type = '3';
            break;
        case 'W':
            type = '4';
            break;
        default:
            type = 0;
            qDebug() << "Error in switch instruction during saving file";
        }

        words_vect.push_back(new Word(itemColumn1->text(), itemColumn2->text(), itemColumn3->text(), itemColumn4->text(), type));
    }

    qDebug() << "Rozmiar wektora po uruchomieniu funkcji zapisu" << words_vect.size();

    if(filesaveload.saveFile(words_vect))
    {
        QMessageBox::information(this, "Zapis zakończony", "Zapis pliku powiódł się", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, "Błąd zapisu", "Błąd zapisu do pliku!", QMessageBox::Ok);
    }
}

void Dictionary_MainWindow::on_actionSortuj_kolumna_1_triggered()
{
    modelSortingColumn = 0;
    updateTable();
}

void Dictionary_MainWindow::on_actionSortuj_kolumna_2_triggered()
{
    modelSortingColumn = 2; //sort by the fourth column
    updateTable();
}

void Dictionary_MainWindow::on_actionSortuj_kolumna_3_triggered()
{
    modelSortingColumn = 4; //sort by the last fifth column
    updateTable();
}

void Dictionary_MainWindow::hideAllTableRows()
{
    int rowCount = tableModel->rowCount();

    for(int i = 0; i < rowCount; i++)
    {
        ui->tableView->hideRow(i);
    }
}

void Dictionary_MainWindow::on_lineEdit_FindItem_textChanged(const QString &arg1)
{
    QList<QStandardItem*> matched_items_PL = tableModel->findItems(arg1, Qt::MatchStartsWith, 0);
    QList<QStandardItem*> matched_items_GER = tableModel->findItems(arg1, Qt::MatchStartsWith, 2);
    QList<QStandardItem*> matched_items_Plural = tableModel->findItems(arg1, Qt::MatchStartsWith, 3);

    hideAllTableRows();

    for(auto item : matched_items_PL)
    {
        ui->tableView->showRow(item->row());
    }
    for(auto item : matched_items_GER)
    {
        ui->tableView->showRow(item->row());
    }
    for(auto item : matched_items_Plural)
    {
        ui->tableView->showRow(item->row());
    }
}

void Dictionary_MainWindow::on_actionQuit_triggered()
{
    QMessageBox::information(this, "BRAK IMPLEMENTACJI", "Jeszcze nie zaimplementowano ;-)");

    //    QMessageBox::question(this, "Czy zapisac?", "Czy zapisać słówka do pliku?", QMessageBox::Yes, QMessageBox::No);

    //    FileSaveLoad filesaveload(this);
    //    filesaveload.SaveFile(words_vect);
}

void Dictionary_MainWindow::on_actionTestMode_triggered()
{
//    testmode = new TestMode(words_vect, this);

//    connect(testmode, SIGNAL(destroyed(QObject*)), this, SLOT(show()));

//    this->hide();
//    testmode->show();
}

void Dictionary_MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Nacisnieto:" << event->text();

    if(event->text() == "n")
    {
        on_actionAdd_word_triggered(); //pressing n is the same as clicking add word button
    }
}

Dictionary_MainWindow::~Dictionary_MainWindow()
{
    for(Word* Item : words_vect)
    {
        delete Item;
    }

    delete soundplayer;
    delete ui;
}


