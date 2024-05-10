#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class settingsform;
}

class settingsform : public QWidget
{
    Q_OBJECT

public:
    explicit settingsform(QWidget *parent = nullptr);
    ~settingsform();

private:
    Ui::settingsform *ui;
};

#endif // SETTINGSFORM_H
