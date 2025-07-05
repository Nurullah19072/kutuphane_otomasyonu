#ifndef ODUNCALMA_H
#define ODUNCALMA_H

#include <QDialog>
#include <QMainWindow>
#include <QSql>
#include <QsqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class oduncalma;
}

class oduncalma : public QDialog
{
    Q_OBJECT

public:
    explicit oduncalma(QSqlDatabase,QWidget *parent = nullptr);
    ~oduncalma();
    void ekrana_yazdır();

private slots:
    void on_odunc_al_pushButton_clicked();

    void on_tum_uyeler_tableView_clicked(const QModelIndex &index);

    void on_tum_kitaplar_tableView_3_clicked(const QModelIndex &index);

private:
    Ui::oduncalma *ui;
    QSqlQuery *sorgu;
    QSqlQuery *sorgu1;
    QSqlQuery *sorgu2;
    int kitap_sayi;
};

#endif // ODUNCALMA_H
