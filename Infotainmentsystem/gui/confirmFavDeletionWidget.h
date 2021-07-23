#ifndef CONFIRMFAVDELETIONWIDGET_H
#define CONFIRMFAVDELETIONWIDGET_H

#include <QDialog>

class MultimediaPlayerWidget;
class QDialogButtonBox;

namespace Ui {
class ConfirmFavDeletionWidget;
}

class ConfirmFavDeletionWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmFavDeletionWidget(MultimediaPlayerWidget* media_class, QWidget *parent = nullptr);
    ~ConfirmFavDeletionWidget();

private:
    Ui::ConfirmFavDeletionWidget *ui;
    MultimediaPlayerWidget* mediaplayer;
    QDialogButtonBox *buttonbox;

private slots:
    void okay();
};

#endif // CONFIRMFAVDELETIONWIDGET_H
