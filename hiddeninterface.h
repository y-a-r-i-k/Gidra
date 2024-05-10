#ifndef HIDDENINTERFACE_H
#define HIDDENINTERFACE_H

#include <QDialog>

namespace Ui {
class hiddeninterface;
}

class hiddeninterface : public QDialog
{
    Q_OBJECT

public:
    explicit hiddeninterface(QWidget *parent = nullptr);
    ~hiddeninterface();

private slots:

    void on_usekeyPushButton_clicked();

    void on_genKeyPushButton_clicked();

private:
    Ui::hiddeninterface *ui;
};

#endif // HIDDENINTERFACE_H
