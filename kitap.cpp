//Nurullah Yıldırım 22100011045
#include "kitap.h"
#include "ui_kitap.h"

kitap::kitap(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::kitap)
{
    ui->setupUi(this);
    sorgu =new QSqlQuery(database);
    kontrol=new QSqlQuery(database);
    sorgu1=new QSqlQuery(database);
    oduncmodel=new QSqlQueryModel();
    sorgu2=new QSqlQuery(database);
    oduncmodel1=new QSqlQueryModel();
    kitap_bilgileri_goster();
}

kitap::~kitap()
{
    delete ui;
}

void kitap::kitap_bilgileri_goster()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec()){

        QMessageBox::critical(this,"HATA!",sorgu->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery(*sorgu);
    ui->tum_kitaplar_tableView->setModel(model);

}





void kitap::on_yeni_kayit_pushButton_clicked()
{


    if(ui->kitap_ad_lineEdit_2->text()=="" || ui->kitap_stok_lineEdit_3->text()=="" ){
        QMessageBox::critical(this,"HATA!","Eksik veri girmeyiniz","Ok");
        return;
    }

    else{
        sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?) ");
        sorgu->addBindValue(ui->kitap_ad_lineEdit_2->text());
        sorgu->addBindValue(ui->kitap_stok_lineEdit_3->text().toInt());

        if(!sorgu->exec()){
            QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
            return;
        }
        ui->kitap_ad_lineEdit_2->clear();
        ui->kitap_stok_lineEdit_3->clear();
        kitap_bilgileri_goster();

    }
}


void kitap::on_guncelle_pushButton_2_clicked()
{
    if(ui->kitap_ad_lineEdit_2->text()=="" || ui->kitap_stok_lineEdit_3->text()=="" ){
        QMessageBox::critical(this,"HATA!","Eksik veri girmeyiniz","Ok");
        return;
    }

    sorgu->prepare("update kitap set kitap_ad=? ,kitap_sayisi=? where kitap_no=? ");
    sorgu->addBindValue(ui->kitap_ad_lineEdit_2->text());
    sorgu->addBindValue(ui->kitap_stok_lineEdit_3->text().toInt());
    sorgu->addBindValue(ui->kitap_no_lineEdit->text().toInt());
    sorgu->exec();

    if(!sorgu->exec()){
        QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
        return;
    }

    ui->kitap_no_lineEdit->clear();
    ui->kitap_ad_lineEdit_2->clear();
    ui->kitap_stok_lineEdit_3->clear();
    kitap_bilgileri_goster();
}




void kitap::on_sil_pushButton_3_clicked()
{
    int silinecek_id=ui->kitap_no_lineEdit->text().toInt();
    kontrol->prepare("select * from odunc_alinan where kitap_no=? ");
    kontrol->addBindValue(silinecek_id);

    if(!kontrol->exec()){
        QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
        return;
    }

    if(!(kontrol->next())){
        sorgu->prepare("delete from kitap where kitap_no=?");
        sorgu->addBindValue(silinecek_id);
        sorgu->exec();
        kitap_bilgileri_goster();

    }

    else{

        QMessageBox::critical(this,"HATA!","Bu üye silinemez.Üyenin teslim etmediği kitaplar bulunmaktadır","Ok");

    }
    ui->kitap_no_lineEdit->clear();
    ui->kitap_ad_lineEdit_2->clear();
    ui->kitap_stok_lineEdit_3->clear();

}






void kitap::on_tum_kitaplar_tableView_clicked(const QModelIndex &index)
{
    QAbstractItemModel *model1=ui->tum_kitaplar_tableView->model();
    ui->kitap_no_lineEdit->setText(model1->index(index.row(),0).data().toString());
    ui->kitap_ad_lineEdit_2->setText(model1->index(index.row(),1).data().toString());
    ui->kitap_stok_lineEdit_3->setText(model1->index(index.row(),2).data().toString());


    sorgu1->prepare("select * from odunc_alinan where kitap_no=? ");
    sorgu1->addBindValue(ui->kitap_no_lineEdit->text());

    if(!sorgu1->exec()){
        QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
        return;
    }

    oduncmodel->setQuery(*sorgu1);
    ui->kitap_odunc_tableView_2->setModel(oduncmodel);


    sorgu2->prepare("select * from odunc_teslim_edilen where kitap_no=? ");
    sorgu2->addBindValue(ui->kitap_no_lineEdit->text());

    if(!sorgu2->exec()){
        QMessageBox::critical(this,"HATA!","Veritabanı sorgusu başarısız: " + sorgu->lastError().text(),"Ok");
        return;
    }

    oduncmodel1->setQuery(*sorgu2);
    ui->kitap_onceden_odunc_tableView_3->setModel(oduncmodel1);



}





