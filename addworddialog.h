#ifndef ADDWORDDIALOG_H
#define ADDWORDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class AddWordDialog;
}

class AddWordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddWordDialog(QWidget *parent = 0);
    QString getWord_To_Add_PL();
    QString getWord_To_Add_Article();
    QString getWord_To_Add_GER();
    QString getWord_To_Add_Plural();
    char getWordType();

    ~AddWordDialog();

private slots:
    void on_AddWord_Button_clicked();
    void on_Cancel_Button_clicked();

    void on_pushButton_umlaut_a_clicked();

    void on_pushButton_umlaut_o_clicked();

    void on_pushButton_umlaut_u_clicked();

    void on_pushButton_scharfes_s_clicked();

    void on_radioButton_Rzeczownik_clicked();

    void on_radioButton_Czasownik_clicked();

    void on_radioButton_Przymiotnik_clicked();

    void on_radioButton_ZlozenieSlow_clicked();

private:
    Ui::AddWordDialog *ui;

    QString word_to_add_PL;
    QString word_to_add_Article;
    QString word_to_add_GER;
    QString word_to_add_Plural;
    char word_type;
};

#endif // ADDWORDDIALOG_H
