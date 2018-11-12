#include "editworddialog.h"
#include "ui_editworddialog.h"

EditWordDialog::EditWordDialog(QVector<QString> itemsinrow_vect, QWidget *parent) :
    QDialog(parent), ui(new Ui::EditWordDialog)
{
    ui->setupUi(this);

//    ui->lineEdit_slowoPOL->setText(itemsinrow_vect.at(0));
//    //ui->lineEdit_rodzajnik->setText(itemsinrow_vect.at(1));
//    ui->lineEdit_slowoGER->setText(itemsinrow_vect.at(2));
//    ui->lineEdit_liczbamnoga->setText(itemsinrow_vect.at(3));

//    if(itemsinrow_vect.at(4) == "1")
//    {
//        ui->radioButton_Rzeczownik->setChecked(true);
//    }
//    else if(itemsinrow_vect.at(4) == "2")
//    {
//        ui->radioButton_Czasownik->setChecked(true);
//    }
//    else if(itemsinrow_vect.at(4) == "3")
//    {
//        ui->radioButton_Przymiotnik->setChecked(true);
//    }
//    else if(itemsinrow_vect.at(4) == "4")
//    {
//        ui->radioButton_ZlozenieSlow->setChecked(true);
//    }
//    else
//    {
//        qDebug() << "Nieznana czesc mowy w oknie edycji slowa";
//    }
}

QString EditWordDialog::getWord_To_Add_PL()
{
    return word_to_add_PL;
}

QString EditWordDialog::getWord_To_Add_Article()
{
    return word_to_add_Article;
}

QString EditWordDialog::getWord_To_Add_GER()
{
    return word_to_add_GER;
}

QString EditWordDialog::getWord_To_Add_Plural()
{
    return word_to_add_Plural;
}

char EditWordDialog::getWordType()
{
    return word_type;
}

void EditWordDialog::on_Ok_Button_clicked()
{
//    if((ui->lineEdit_slowoPOL->text().size() <= 1 || ui->lineEdit_slowoGER->text().size() <= 1) || (ui->lineEdit_rodzajnik->text() != "der" && ui->lineEdit_rodzajnik->text() != "die" && ui->lineEdit_rodzajnik->text() != "das" && ui->lineEdit_rodzajnik->text() != "") || !(ui->radioButton_Rzeczownik->isChecked() || ui->radioButton_Czasownik->isChecked() || ui->radioButton_Przymiotnik->isChecked() || ui->radioButton_ZlozenieSlow->isChecked()))
//    {
//        QMessageBox::warning(this, "Podano nieprawidłowe dane", "Słowo jest zbyt krótkie, nie wybrano części mowy lub wpisano błędny rodzajnik, spróbuj jeszcze raz", QMessageBox::Ok);
//    }
//    else
//    {
//        word_to_add_PL = ui->lineEdit_slowoPOL->text();
//        word_to_add_Article = ui->lineEdit_rodzajnik->text();
//        word_to_add_GER = ui->lineEdit_slowoGER->text();
//        word_to_add_Plural = ui->lineEdit_liczbamnoga->text();

//        if(ui->radioButton_Rzeczownik->isChecked())
//        {
//            word_type = '1';
//        }
//        else if(ui->radioButton_Czasownik->isChecked())
//        {
//            word_type = '2';
//        }
//        else if(ui->radioButton_Przymiotnik->isChecked())
//        {
//            word_type = '3';
//        }
//        else if(ui->radioButton_ZlozenieSlow->isChecked())
//        {
//            word_type = '4';
//        }
//        else
//        {
//            qDebug() << "Something went wrong while choosing word type";
//        }

//        qDebug() << "Typ przed wyjsciem z dialogu wynosi: " << word_type;

//        accept();
//    }
}

void EditWordDialog::on_Cancel_Button_clicked()
{
    close();
}


void EditWordDialog::on_pushButton_umlaut_a_clicked()
{
//    if(ui->lineEdit_slowoGER->hasFocus())
//    {
//        ui->lineEdit_slowoGER->insert("ä");
//    }
//    else if(ui->lineEdit_liczbamnoga->hasFocus())
//    {
//        ui->lineEdit_liczbamnoga->insert("ä");
//    }
//    else
//    {
//        qDebug() << "No window or wrong window is focused";
//    }
}

void EditWordDialog::on_pushButton_umlaut_o_clicked()
{
//    if(ui->lineEdit_slowoGER->hasFocus())
//    {
//        ui->lineEdit_slowoGER->insert("ö");
//    }
//    else if(ui->lineEdit_liczbamnoga->hasFocus())
//    {
//        ui->lineEdit_liczbamnoga->insert("ö");
//    }
//    else
//    {
//        qDebug() << "No window or wrong window is focused";
//    }
}

void EditWordDialog::on_pushButton_umlaut_u_clicked()
{
//    if(ui->lineEdit_slowoGER->hasFocus())
//    {
//        ui->lineEdit_slowoGER->insert("ü");
//    }
//    else if(ui->lineEdit_liczbamnoga->hasFocus())
//    {
//        ui->lineEdit_liczbamnoga->insert("ü");
//    }
//    else
//    {
//        qDebug() << "No window or wrong window is focused";
//    }
}

void EditWordDialog::on_pushButton_scharfes_s_clicked()
{
//    if(ui->lineEdit_slowoGER->hasFocus())
//    {
//        ui->lineEdit_slowoGER->insert("ß");
//    }
//    else if(ui->lineEdit_liczbamnoga->hasFocus())
//    {
//        ui->lineEdit_liczbamnoga->insert("ß");
//    }
//    else
//    {
//        qDebug() << "No window or wrong window is focused";
//    }
}

EditWordDialog::~EditWordDialog()
{
    delete ui;
}

