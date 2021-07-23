#include "ui_ConfirmFavDeletionWidget.h"

#include "gui/confirmFavDeletionWidget.h"
#include "gui/multimediaPlayerWidget.h"

ConfirmFavDeletionWidget::ConfirmFavDeletionWidget(MultimediaPlayerWidget *media_class, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmFavDeletionWidget)
{
    ui->setupUi(this);

    mediaplayer = media_class;

    buttonbox = ConfirmFavDeletionWidget::findChild<QDialogButtonBox *>("buttonBox");

    connect(buttonbox, &QDialogButtonBox::accepted, this, &ConfirmFavDeletionWidget::okay);
    connect(buttonbox, &QDialogButtonBox::rejected, this, &ConfirmFavDeletionWidget::hide);
}

ConfirmFavDeletionWidget::~ConfirmFavDeletionWidget()
{
    delete ui;
}

void ConfirmFavDeletionWidget::okay()
{
    mediaplayer->delete_favs_confirmed();
    this->hide();
}
