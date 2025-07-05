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

