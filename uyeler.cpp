//Nurullah Yıldırım 22100011045
#include "uyeler.h"
#include "ui_uyeler.h"



uyeler::uyeler(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::uyeler)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(database);
    kontrol=new QSqlQuery(database);
    uye_bilgileri_goster();
}

uyeler::~uyeler()
{
    delete ui;
}

void uyeler::uye_bilgileri_goster()
{
    sorgu->prepare("select * from uye");
    if(!sorgu->exec()){

        QMessageBox::critical(this,"HATA!",sorgu->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery(*sorgu);
    ui->tum_uyeler_tableView->setModel(model);

}


void uyeler::on_yeni_kayit_pushButton_3_clicked()
{

    if(ui->uye_ad_lineEdit_3->text()=="" || ui->uye_soyad_lineEdit_2->text()=="" ){
        QMessageBox::critical(this,"HATA!","Eksik veri girmeyiniz","Ok");
        return;
    }

    else{
        sorgu->prepare("insert into uye(uye_ad,uye_soyad) values(?,?) ");
        sorgu->addBindValue(ui->uye_ad_lineEdit_3->text());
        sorgu->addBindValue(ui->uye_soyad_lineEdit_2->text());

        if(!sorgu->exec()){
            QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
            return;
        }
        ui->uye_ad_lineEdit_3->clear();
        ui->uye_soyad_lineEdit_2->clear();
        uye_bilgileri_goster();

    }

}


void uyeler::on_guncelle_pushButton_2_clicked()
{
    if(ui->uye_ad_lineEdit_3->text()=="" || ui->uye_soyad_lineEdit_2->text()=="" ){
        QMessageBox::critical(this,"HATA!","Eksik veri girmeyiniz","Ok");

        return;
    }

    sorgu->prepare("update uye set uye_ad=? ,uye_soyad=? where uye_no=? ");
    sorgu->addBindValue(ui->uye_ad_lineEdit_3->text());
    sorgu->addBindValue(ui->uye_soyad_lineEdit_2->text());
    sorgu->addBindValue(ui->uye_no_lineEdit->text().toInt());
    sorgu->exec();

    if(!sorgu->exec()){
        QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
        return;
    }
    ui->uye_no_lineEdit->clear();
    ui->uye_ad_lineEdit_3->clear();
    ui->uye_soyad_lineEdit_2->clear();
    uye_bilgileri_goster();


}





void uyeler::on_tum_uyeler_tableView_clicked(const QModelIndex &index)
{
    QAbstractItemModel *model1=ui->tum_uyeler_tableView->model();
    ui->uye_no_lineEdit->setText(model1->index(index.row(),0).data().toString());
    ui->uye_ad_lineEdit_3->setText(model1->index(index.row(),1).data().toString());
    ui->uye_soyad_lineEdit_2->setText(model1->index(index.row(),2).data().toString());
}



void uyeler::on_sil_pushButton_clicked()
{
    int silinecek_id=ui->uye_no_lineEdit->text().toInt();
    kontrol->prepare("select * from odunc_alinan where uye_no=? ");
    kontrol->addBindValue(silinecek_id);

    if(!kontrol->exec()){
        QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
        return;
    }

    if(!(kontrol->next())){
        sorgu->prepare("delete from uye where uye_no=?");
        sorgu->addBindValue(silinecek_id);
        sorgu->exec();
        uye_bilgileri_goster();

    }

    else{

        QMessageBox::critical(this,"HATA!","Bu üye silinemez.Üyenin teslim etmediği kitaplar bulunmaktadır","Ok");

    }
    ui->uye_no_lineEdit->clear();
    ui->uye_ad_lineEdit_3->clear();
    ui->uye_soyad_lineEdit_2->clear();


}

