#ifndef ADDNEWFAVOURITEWIDGET_H
#define ADDNEWFAVOURITEWIDGET_H

#include <QDialog>

class MultimediaPlayer;
class QDialogButtonBox;

namespace Ui {
class AddNewFavouriteWidget;
}

class AddNewFavouriteWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewFavouriteWidget(MultimediaPlayer *media_class, QWidget *parent = nullptr);
    ~AddNewFavouriteWidget();
    QString geturl();
    QString getname();
    void prepare_window();

private:
    Ui::AddNewFavouriteWidget *ui;
    QDialogButtonBox *buttonbox;
    QString fav_name;
    QString fav_url;
    MultimediaPlayer* mediaplayer;

private slots:
    void okay();

signals:
    void favourite_added_signal();
};

#endif // ADDNEWFAVOURITEWIDGET_H
