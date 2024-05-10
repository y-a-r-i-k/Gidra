#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"
#include "loginform.h"
#include "hiddeninterface.h"

#include <QTranslator>
#include <QMessageBox>

#include <QFileDialog>

#include <string>
#include <iostream>


settingsdialog::settingsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsdialog)
{
    ui->setupUi(this);

    CtrlShiftG = new QShortcut(this);
    CtrlShiftG->setKey(Qt::CTRL + Qt::Key_G);

    connect(CtrlShiftG, SIGNAL(activated()), this, SLOT(hidden_interface()));
}

settingsdialog::~settingsdialog()
{
    delete ui;
}


void settingsdialog::on_styleComboBox_activated(int index)
{
    this->wasTouched = true;
}



void settingsdialog::on_ApplyButton_clicked()
{


//    //Lang settings
//    if (ui->languageComboBox->currentIndex() == 0) //English
//    {
//        settings.setValue("/Settings/lang", 0);
//    }
//    else if (ui->languageComboBox->currentIndex() == 1) //Russian
//    {
//        settings.setValue("/Settings/lang", 1);
//    }
//    else if (ui->languageComboBox->currentIndex() == 2) //German
//    {
//        settings.setValue("/Settings/lang", 2);
//    }

}


void settingsdialog::on_CloseButton_clicked()
{
    close();
}




void settingsdialog::on_SetNewPassPushButton_clicked()
{
    settings.setValue("/SetPassword/Password", ui->newPasswordLineEdit->text());
}


void settingsdialog::on_pathPushButton_clicked()
{
    this->fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Choose"), QDir::rootPath(), "Tables (*.csv);; All files (*.*)");

    ui->exportPathlineEdit->setText(this->fileName);
}


void settingsdialog::on_applyStyleSettingsPushButton_clicked()
{
    //Style settings
    if ((ui->styleComboBox->currentIndex() == 0) && (this->wasTouched))
    {
        settings.setValue("/Settings/color", 0);
    }
    else if ((ui->styleComboBox->currentIndex() == 1)  && (this->wasTouched))
    {
        settings.setValue("/Settings/color", 1);
    }
}


void settingsdialog::on_exportPushButton_clicked()
{
    ui->exportPathlineEdit->setText(QFileDialog::getSaveFileName(this, tr("Save CSV"),"./" ,"CSV (*.csv)"));
    MainWindow mw;
    mw.saveAsCSV(ui->exportPathlineEdit->text());
}

void settingsdialog::hidden_interface()
{
    hiddeninterface hidden;

    hidden.setModal(true);
    hidden.exec();
}

