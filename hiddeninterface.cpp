#include "hiddeninterface.h"
#include "ui_hiddeninterface.h"

#include "mainwindow.h"

#include <QSysInfo>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "QStringEncryptionXOR.h"

hiddeninterface::hiddeninterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hiddeninterface)
{
    ui->setupUi(this);
}

hiddeninterface::~hiddeninterface()
{
    delete ui;
}

void hiddeninterface::on_usekeyPushButton_clicked()
{
    MainWindow mw;

    QString keyFromFile;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Key..."), "/", tr("Text files (*.txt)"));

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        keyFromFile = QStringEncryptionXOR::cryptString(file.readAll());
    }

    mw.setPasswordsModel(keyFromFile);

    this->close();
}


void hiddeninterface::on_genKeyPushButton_clicked()
{
    QSysInfo sysinfo;

    QString systemInformation = "Gidra";
    systemInformation.append(sysinfo.currentCpuArchitecture());
    systemInformation.append(sysinfo.productVersion());
    systemInformation.append(sysinfo.machineUniqueId());
    systemInformation.append("Project");

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Key"), "../gidra_key.txt", tr("Text files (*.txt)"));

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream qts (&file);
        qts << QStringEncryptionXOR::cryptString(systemInformation);
        file.close();
    }

    this->close();
}

