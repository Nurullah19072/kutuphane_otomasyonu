//Nurullah Yıldırım 22100011045
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "uyeler.h"
#include "kitap.h"
#include "oduncalma.h"
#include"oduncteslim.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database.setDatabaseName("Kutuphane.db");
    if(!database.open()){

        ui->statusbar->showMessage("Veri tabanına bağlanılamadı!");

    }

    else{
        ui->statusbar->showMessage("Veri tabanına bağlanıldı!");

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_uye_islemleri_pushButton_clicked()
{
    uyeler *uye=new uyeler(database,this);
    uye->exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    kitap *kitap1=new kitap(database,this);
    kitap1->exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    oduncalma *odunc=new oduncalma(database);
    odunc->exec();

}


void MainWindow::on_pushButton_4_clicked()
{
    oduncteslim *teslim=new oduncteslim(database);
    teslim->exec();
}

