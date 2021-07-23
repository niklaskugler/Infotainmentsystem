#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = nullptr);
    void update_color(int x);

private:
    QString color_palette[6];
};

#endif // SETTINGS_H
