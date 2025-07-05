#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSql>
#include <QsqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_uye_islemleri_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *sorgu;
};
#endif // MAINWINDOW_H
