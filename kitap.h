#ifndef KITAP_H
#define KITAP_H


#include <QDialog>
#include <QMainWindow>
#include <QSql>
#include <QsqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class kitap;
}

class kitap : public QDialog
{
    Q_OBJECT

public:
    explicit kitap(QSqlDatabase,QWidget *parent = nullptr);
    ~kitap();
    void kitap_bilgileri_goster();



private slots:
    void on_yeni_kayit_pushButton_clicked();

    void on_guncelle_pushButton_2_clicked();

    void on_tum_kitaplar_tableView_clicked(const QModelIndex &index);

    void on_sil_pushButton_3_clicked();

private:
    Ui::kitap *ui;
    QSqlQuery *sorgu;
    QSqlQuery *kontrol;
    QSqlQuery *sorgu1;
    QSqlQueryModel *oduncmodel;
    QSqlQuery *sorgu2;
    QSqlQueryModel *oduncmodel1;

};

#endif // KITAP_H
