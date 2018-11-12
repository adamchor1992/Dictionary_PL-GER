#ifndef EDITWORDDIALOG_H
#define EDITWORDDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>

namespace Ui {
class EditWordDialog;
}

class EditWordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditWordDialog(QVector<QString> itemsinrow_vect, QWidget *parent = 0);
    QString getWord_To_Add_PL();
    QString getWord_To_Add_Article();
    QString getWord_To_Add_GER();
    QString getWord_To_Add_Plural();
    char getWordType();

    ~EditWordDialog();

private slots:

    void on_Ok_Button_clicked();

    void on_Cancel_Button_clicked();

    void on_pushButton_umlaut_a_clicked();

    void on_pushButton_umlaut_o_clicked();

    void on_pushButton_umlaut_u_clicked();

    void on_pushButton_scharfes_s_clicked();

private:
    Ui::EditWordDialog *ui;

    QString word_to_add_PL;
    QString word_to_add_Article;
    QString word_to_add_GER;
    QString word_to_add_Plural;
    char word_type;
};

#endif // EDITWORDDIALOG_H
