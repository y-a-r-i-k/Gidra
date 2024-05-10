#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

#include <QShortcut>
#include "QSettings"
#include "QVariant"


namespace Ui {
class loginform;
}

class loginform : public QWidget
{
    Q_OBJECT

public:
    explicit loginform(QWidget *parent = nullptr);
    ~loginform();

private slots:
    void on_loginButton_clicked();
    void login();

    void on_showCheckBox_stateChanged(int arg1);


private:
    Ui::loginform *ui;

    QVariant pass;
    QVariant databasepassword;

    bool shown;

    QShortcut *loginByEnter;

};

#endif // LOGINFORM_H
