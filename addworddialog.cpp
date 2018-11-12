#include "addworddialog.h"
#include "ui_addword_dialog.h"

AddWordDialog::AddWordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWordDialog)
{
    ui->setupUi(this);

    ui->radioButton_Rzeczownik->setChecked(true); //radio button rzeczownik is checked by default

    word_type = 0;
}

QString AddWordDialog::getWord_To_Add_PL()
{
    return word_to_add_PL;
}

QString AddWordDialog::getWord_To_Add_Article()
{
    return word_to_add_Article;
}

QString AddWordDialog::getWord_To_Add_GER()
{
    return word_to_add_GER;
}

QString AddWordDialog::getWord_To_Add_Plural()
{
    return word_to_add_Plural;
}

char AddWordDialog::getWordType()
{
    return word_type;
}

void AddWordDialog::on_AddWord_Button_clicked()
{
    if(ui->radioButton_Rzeczownik->isChecked()) //rzeczownik is chosen
    {
        if(ui->lineEdit_wordInPolish->text().isEmpty() || ui->lineEdit_wordInGerman->text().isEmpty() || ui->lineEdit_pluralWordInGerman->text().isEmpty())
        {
            QMessageBox::warning(this, "Podano nieprawidłowe dane", "Nic nie wpisano!", QMessageBox::Ok);
            return;
        }
        else if(ui->comboBox_article->currentIndex() == 0) //no article chosen
        {
            QMessageBox::warning(this, "Podano nieprawidłowe dane", "Nie podano rodzajnika, spróbuj jeszcze raz", QMessageBox::Ok);
            return;
        }
        else if(ui->lineEdit_pluralWordInGerman->text().size() == 0)
        {
            QMessageBox::warning(this, "Podano nieprawidłowe dane", "Nie podano liczby mnogiej (jeśli brak liczby mnogiej wpisz '-'), spróbuj jeszcze raz", QMessageBox::Ok);
            return;
        }
        else if(ui->lineEdit_wordInGerman->text().at(0).isLower() || ui->lineEdit_pluralWordInGerman->text().at(0).isLower())
        {
            QMessageBox::warning(this, "Podano nieprawidłowe dane", "Podano rzeczownik napisany z małej litery, spróbuj jeszcze raz", QMessageBox::Ok);
            return;
        }
    }
    else if(!(ui->radioButton_Rzeczownik->isChecked())) //if any other radio button chosen
    {
        if(ui->lineEdit_wordInPolish->text().isEmpty() || ui->lineEdit_wordInGerman->text().isEmpty())
        {
            QMessageBox::warning(this, "Podano nieprawidłowe dane", "Nic nie wpisano!", QMessageBox::Ok);
            return;
        }
    }

    word_to_add_PL = ui->lineEdit_wordInPolish->text();
    word_to_add_Article = ui->comboBox_article->currentText();
    word_to_add_GER = ui->lineEdit_wordInGerman->text();
    word_to_add_Plural = ui->lineEdit_pluralWordInGerman->text();

    if(ui->radioButton_Rzeczownik->isChecked())
    {
        word_type = '1';
    }
    else if(ui->radioButton_Czasownik->isChecked())
    {
        word_type = '2';
    }
    else if(ui->radioButton_Przymiotnik->isChecked())
    {
        word_type = '3';
    }
    else if(ui->radioButton_ZlozenieSlow->isChecked())
    {
        word_type = '4';
    }
    else
    {
        qDebug() << "Something went wrong while choosing word type";
    }

    qDebug() << "Typ przed wyjsciem z dialogu wynosi: " << word_type;

    accept();

}

void AddWordDialog::on_Cancel_Button_clicked()
{
    close();
}

void AddWordDialog::on_pushButton_umlaut_a_clicked()
{
    if(ui->lineEdit_wordInGerman->hasFocus())
    {
        ui->lineEdit_wordInGerman->insert("ä");
    }
    else if(ui->lineEdit_pluralWordInGerman->hasFocus())
    {
        ui->lineEdit_pluralWordInGerman->insert("ä");
    }
    else
    {
        qDebug() << "No window or wrong window is focused";
    }
}

void AddWordDialog::on_pushButton_umlaut_o_clicked()
{
    if(ui->lineEdit_wordInGerman->hasFocus())
    {
        ui->lineEdit_wordInGerman->insert("ö");
    }
    else if(ui->lineEdit_pluralWordInGerman->hasFocus())
    {
        ui->lineEdit_pluralWordInGerman->insert("ö");
    }
    else
    {
        qDebug() << "No window or wrong window is focused";
    }
}

void AddWordDialog::on_pushButton_umlaut_u_clicked()
{
    if(ui->lineEdit_wordInGerman->hasFocus())
    {
        ui->lineEdit_wordInGerman->insert("ü");
    }
    else if(ui->lineEdit_pluralWordInGerman->hasFocus())
    {
        ui->lineEdit_pluralWordInGerman->insert("ü");
    }
    else
    {
        qDebug() << "No window or wrong window is focused";
    }
}

void AddWordDialog::on_pushButton_scharfes_s_clicked()
{
    if(ui->lineEdit_wordInGerman->hasFocus())
    {
        ui->lineEdit_wordInGerman->insert("ß");
    }
    else if(ui->lineEdit_pluralWordInGerman->hasFocus())
    {
        ui->lineEdit_pluralWordInGerman->insert("ß");
    }
    else
    {
        qDebug() << "No window or wrong window is focused";
    }
}

void AddWordDialog::on_radioButton_Rzeczownik_clicked()
{
    ui->comboBox_article->setEnabled(true);
    ui->comboBox_article->setCurrentIndex(0);
    ui->lineEdit_pluralWordInGerman->setText("");
    ui->lineEdit_pluralWordInGerman->setEnabled(true);

    this->update();
}

void AddWordDialog::on_radioButton_Czasownik_clicked()
{
    ui->comboBox_article->setEnabled(false);
    ui->comboBox_article->setCurrentIndex(0);
    ui->lineEdit_pluralWordInGerman->setText("");
    ui->lineEdit_pluralWordInGerman->setEnabled(false);

    this->update();
}

void AddWordDialog::on_radioButton_Przymiotnik_clicked()
{
    ui->comboBox_article->setEnabled(false);
    ui->comboBox_article->setCurrentIndex(0);
    ui->lineEdit_pluralWordInGerman->setText("");
    ui->lineEdit_pluralWordInGerman->setEnabled(false);

    this->update();
}

void AddWordDialog::on_radioButton_ZlozenieSlow_clicked()
{
    ui->comboBox_article->setEnabled(false);
    ui->comboBox_article->setCurrentIndex(0);
    ui->lineEdit_pluralWordInGerman->setText("");
    ui->lineEdit_pluralWordInGerman->setEnabled(false);

    this->update();
}

AddWordDialog::~AddWordDialog()
{
    delete ui;
}
