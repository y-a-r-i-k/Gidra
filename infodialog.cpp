#include "infodialog.h"
#include "ui_infodialog.h"

#include "QUrl"
#include "QDesktopServices"


infodialog::infodialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infodialog)
{
    ui->setupUi(this);
}

infodialog::~infodialog()
{
    delete ui;
}

void infodialog::on_closeButton_clicked()
{
    close();
}


void infodialog::on_manualButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://y-a-r-i-k.github.io/Gidra/manual.html"));
}

