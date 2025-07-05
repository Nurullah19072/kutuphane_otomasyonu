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

