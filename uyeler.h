#ifndef UYELER_H
#define UYELER_H

#include <QDialog>
#include <QMainWindow>
#include <QSql>
#include <QsqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class uyeler;
}

class uyeler : public QDialog
{
    Q_OBJECT

public:
    explicit uyeler(QSqlDatabase,QWidget *parent = nullptr);
    ~uyeler();
    void uye_bilgileri_goster();

private slots:
    void on_yeni_kayit_pushButton_3_clicked();

    void on_guncelle_pushButton_2_clicked();

    void on_tum_uyeler_tableView_clicked(const QModelIndex &index);

    void on_sil_pushButton_clicked();

private:
    Ui::uyeler *ui;
    QSqlQuery *sorgu;
    QSqlQuery *kontrol;
};

#endif // UYELER_H
