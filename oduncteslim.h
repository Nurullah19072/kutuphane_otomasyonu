#ifndef ODUNCTESLIM_H
#define ODUNCTESLIM_H

#include <QDialog>
#include <QMainWindow>
#include <QSql>
#include <QsqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlError>
#include <QCoreApplication>
#include <QDate>
#include <QDebug>

namespace Ui {
class oduncteslim;
}

class oduncteslim : public QDialog
{
    Q_OBJECT

public:
    explicit oduncteslim(QSqlDatabase ,QWidget *parent = nullptr);
    ~oduncteslim();
    void ekrana_yazdır();

private slots:
    void on_odunc_teslim_pushButton_clicked();

    void on_odunc_tableView_clicked(const QModelIndex &index);

private:
    Ui::oduncteslim *ui;
    QSqlQuery *sorgu;
    QSqlQuery *sorgu1;
    QString tarih;
};

#endif // ODUNCTESLIM_H
