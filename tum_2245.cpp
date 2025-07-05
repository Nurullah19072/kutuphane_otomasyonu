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





//Nurullah Yıldırım 22100011045
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


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


//Nurullah Yıldırım 22100011045
#include "oduncalma.h"
#include "ui_oduncalma.h"

oduncalma::oduncalma(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::oduncalma)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(database);
    sorgu1=new QSqlQuery(database);
    sorgu2=new QSqlQuery(database);
    ekrana_yazdır();
}

oduncalma::~oduncalma()
{
    delete ui;

}


void oduncalma::ekrana_yazdır()

{   //UYE BİLGİLERİ YAZDIRMA
    sorgu->prepare("select * from uye");
    if(!sorgu->exec()){

        QMessageBox::critical(this,"HATA!",sorgu->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery(*sorgu);
    ui->tum_uyeler_tableView->setModel(model);


    //KİTAP BİLGİLERİ YAZDIRMA
    sorgu1->prepare("select * from kitap");
    if(!sorgu1->exec()){

        QMessageBox::critical(this,"HATA!",sorgu1->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model1=new QSqlQueryModel();

    model1->setQuery(*sorgu1);
    ui->tum_kitaplar_tableView_3->setModel(model1);


    //ÖDÜNÇ ALINAN KİTAPLARI YAZDIRMA
    sorgu2->prepare("select * from odunc_alinan");
    if(!sorgu2->exec()){

        QMessageBox::critical(this,"HATA!",sorgu2->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model2=new QSqlQueryModel();

    model2->setQuery(*sorgu2);
    ui->odunc_alinan_tableView_2->setModel(model2);

}







void oduncalma::on_odunc_al_pushButton_clicked()
{
    int kitapNo = ui->kitap_no_lineEdit->text().toInt();
    QSqlQuery kontrolSorgu1;
    kontrolSorgu1.prepare("select count(*) from odunc_alinan where  kitap_no = ?");
    kontrolSorgu1.addBindValue(kitapNo);

    if (!kontrolSorgu1.exec()) {
        QMessageBox::critical(this,"HATA!",kontrolSorgu1.lastError().text(),"Ok");
        return;
    }

    if(kontrolSorgu1.next()){
        int count1 = kontrolSorgu1.value(0).toInt();
        if(kitap_sayi==count1){

            QMessageBox::critical(this,"HATA!","Stokta seçtiğiniz kitap kalmamıştır.","Ok");
            return;

        }

    }



    if(ui->uye_no_lineEdit_2->text().isEmpty() || ui->kitap_no_lineEdit->text().isEmpty()){
        QMessageBox::critical(this,"HATA!","Lütfen kitap alacak kişinin ve alınacak kitabın üstüne tıklayınız","Ok");
        return;
    }

    int uyeNo = ui->uye_no_lineEdit_2->text().toInt();



    QSqlQuery kontrolSorgu;
    kontrolSorgu.prepare("select count(*) from odunc_alinan where uye_no = ? and kitap_no = ?");
    kontrolSorgu.addBindValue(uyeNo);
    kontrolSorgu.addBindValue(kitapNo);

    if (!kontrolSorgu.exec()) {
        QMessageBox::critical(this,"HATA!",kontrolSorgu.lastError().text(),"Ok");
        return;
    }

    kontrolSorgu.next();
    int count = kontrolSorgu.value(0).toInt();

    if (count > 0) {
        QMessageBox::critical(this,"HATA!","Bu kitap zaten bu üye tarafından ödünç alınmış.","Ok");
        return;
    }


    sorgu2->prepare("insert into odunc_alinan (uye_no, kitap_no, odunc_alma_tarihi) values (?, ?, ?)");
    sorgu2->addBindValue(uyeNo);
    sorgu2->addBindValue(kitapNo);
    sorgu2->addBindValue(ui->odunc_tarih_dateEdit->text());

    if (!sorgu2->exec()) {
        QMessageBox::critical(this,"HATA!",sorgu2->lastError().text(),"Ok");
        return;
    }

    ui->uye_no_lineEdit_2->clear();
    ui->kitap_no_lineEdit->clear();
    ekrana_yazdır();



}




void oduncalma::on_tum_uyeler_tableView_clicked(const QModelIndex &index)
{
    QAbstractItemModel *mmodel1=ui->tum_uyeler_tableView->model();
    ui->uye_no_lineEdit_2->setText(mmodel1->index(index.row(),0).data().toString());

}


void oduncalma::on_tum_kitaplar_tableView_3_clicked(const QModelIndex &index)
{
    QAbstractItemModel *mmodel2=ui->tum_kitaplar_tableView_3->model();
    ui->kitap_no_lineEdit->setText(mmodel2->index(index.row(),0).data().toString());
    kitap_sayi=mmodel2->index(index.row(),2).data().toInt();

}

//Nurullah Yıldırım 22100011045
#include "oduncteslim.h"
#include "ui_oduncteslim.h"

oduncteslim::oduncteslim(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::oduncteslim)
{
    ui->setupUi(this);
    sorgu=new QSqlQuery(database);
    sorgu1=new QSqlQuery(database);
    ekrana_yazdır();
}

oduncteslim::~oduncteslim()
{
    delete ui;
}

void oduncteslim::ekrana_yazdır()
{
    //ÖDÜNÇ ALINAN KİTAPLARI YAZDIRMA
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec()){

        QMessageBox::critical(this,"HATA!",sorgu->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery(*sorgu);
    ui->odunc_tableView->setModel(model);

    //TESLİM EDİLMİŞ KİTAPLARI YAZDIRMA
    sorgu1->prepare("select * from odunc_teslim_edilen");
    if(!sorgu1->exec()){

        QMessageBox::critical(this,"HATA!",sorgu1->lastError().text(),"Ok");
        return;

    }

    QSqlQueryModel *model1=new QSqlQueryModel();

    model1->setQuery(*sorgu1);
    ui->teslim_tableView_2->setModel(model1);


}





void oduncteslim::on_odunc_teslim_pushButton_clicked()
{
    int borc;
    QString alinan_tarih =tarih ;
    QString verilen_tarih =ui->teslim_tarih_dateEdit->text() ;

    // Tarih formatı belirleniyor
    QString format = "dd.MM.yyyy";

    // QDate nesneleri oluşturuluyor
    QDate alinan_tarih1 = QDate::fromString(alinan_tarih, format);
    QDate verilen_tarih1 = QDate::fromString(verilen_tarih, format);

    // Tarihler arasında fark hesaplanıyor
    int fark = alinan_tarih1.daysTo(verilen_tarih1);

    if(fark>15){

     borc= (fark-15)*2;

    }


    else{

        borc=0;
    }


    if(ui->uye_no_lineEdit->text()==""){

        QMessageBox::critical(this,"HATA!","Lütfen teslim edecek kişinin numarasına veya o satırdaki herhangi bir bilgiye tıklayınız","Ok");
    }

    else{

        sorgu1->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?) ");
        sorgu1->addBindValue(ui->uye_no_lineEdit->text().toInt());
        sorgu1->addBindValue(ui->kitap_no_lineEdit_2->text().toInt());
        sorgu1->addBindValue(tarih);
        sorgu1->addBindValue(ui->teslim_tarih_dateEdit->text());
        sorgu1->addBindValue(borc);
        if(!sorgu1->exec()){

            QMessageBox::critical(this,"HATA!",sorgu1->lastError().text(),"Ok");
            return;

        }
        int silinecek_id=ui->uye_no_lineEdit->text().toInt();
        int sil_kitap_id=ui->kitap_no_lineEdit_2->text().toInt();
        sorgu->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
        sorgu->addBindValue(silinecek_id);
        sorgu->addBindValue(sil_kitap_id);
        sorgu->exec();




    }
    ui->uye_no_lineEdit->clear();
    ui->kitap_no_lineEdit_2->clear();
    ekrana_yazdır();



}


void oduncteslim::on_odunc_tableView_clicked(const QModelIndex &index)
{
    QAbstractItemModel *mmodel1=ui->odunc_tableView->model();
    ui->uye_no_lineEdit->setText(mmodel1->index(index.row(),0).data().toString());
    ui->kitap_no_lineEdit_2->setText(mmodel1->index(index.row(),1).data().toString());
    tarih=mmodel1->index(index.row(),2).data().toString();

}

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


