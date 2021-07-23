#include "addNewFavouriteWidget.h"
#include "ui_addNewFavouriteWidget.h"

#include <QDebug>

#include "core/multimediaPlayer.h"

AddNewFavouriteWidget::AddNewFavouriteWidget(MultimediaPlayer* media_class, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewFavouriteWidget)
{
    mediaplayer = media_class;
    fav_name = "";
    fav_url = "";
    ui->setupUi(this);
    buttonbox = AddNewFavouriteWidget::findChild<QDialogButtonBox *>("buttonBox");

    connect(buttonbox, &QDialogButtonBox::accepted, this, &AddNewFavouriteWidget::okay);
    connect(buttonbox, &QDialogButtonBox::rejected, this, &AddNewFavouriteWidget::hide);
}

AddNewFavouriteWidget::~AddNewFavouriteWidget()
{
    delete ui;
}

void AddNewFavouriteWidget::okay()
{
    fav_name = ui->lineEdit_name->text();
    fav_url = ui->lineEdit_url->text();

    if(fav_name != "" && fav_url != "")
        emit favourite_added_signal();

    this->hide();
}

QString AddNewFavouriteWidget::geturl()
{
    return fav_url;
}
QString AddNewFavouriteWidget::getname()
{
    return fav_name;
}

void AddNewFavouriteWidget::prepare_window()
{
    ui->lineEdit_name->setDisabled(false);
    ui->lineEdit_url->setDisabled(false);

    ui->lineEdit_name->clear();
    ui->lineEdit_url->clear();

    int fav_amount = mediaplayer->get_channel_nr()-5;       //berechnet anzahl der favoritenchannel
    if(fav_amount == 5)     //nicht mehr als 5 favoritenchannel erlaubt
    {
       ui->lineEdit_name->setDisabled(true);
       ui->lineEdit_name->setStyleSheet("background-color: rgb(100, 100, 100);");
       ui->lineEdit_url->setDisabled(true);
       ui->lineEdit_url->setStyleSheet("background-color: rgb(100, 100, 100);");
       ui->label_4->setText("Maximale Favoritenanzahl erreicht");
    }
    else
    {
        ui->lineEdit_name->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->lineEdit_url->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->label_4->setText("");
    }
}
