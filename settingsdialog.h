#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTranslator>
#include <QMessageBox>
#include <QSettings>
#include <QShortcut>


namespace Ui {
class settingsdialog;
}

class settingsdialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsdialog(QWidget *parent = nullptr);
    ~settingsdialog();

private slots:


    void on_styleComboBox_activated(int index);

    void on_ApplyButton_clicked();

    void on_CloseButton_clicked();

    void on_SetNewPassPushButton_clicked();

    void on_pathPushButton_clicked();

    void on_exportPushButton_clicked();

    void on_applyStyleSettingsPushButton_clicked();

    void hidden_interface();


private:
    Ui::settingsdialog *ui;
    QTranslator translator;

    QSettings settings;


    bool wasTouched; // For style combo box

    QString fileName; //For export

    QShortcut *CtrlShiftG;

};

#endif // SETTINGSDIALOG_H
