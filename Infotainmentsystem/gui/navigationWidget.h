#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QWidget>
#include <QVariant>

class InfotainmentsystemWindow;
class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class NavigationWidget; }
QT_END_NAMESPACE

class NavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationWidget(InfotainmentsystemWindow *menu, QWidget *parent = nullptr);
    ~NavigationWidget();

private:
    Ui::NavigationWidget *ui;
    QPushButton* HomeButton;
    QWidget* menu_obj;
    QPushButton *side_menu[5];
    InfotainmentsystemWindow* infotainmentsystem_obj;


private slots:
    void go_home();
    void side_menu_clicked();

signals:
    void setCenter(QVariant, QVariant);
    void homeButtonClicked();
};

#endif // NAVIGATIONWIDGET_H
