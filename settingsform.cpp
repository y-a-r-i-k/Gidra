#include "settingsform.h"
#include "ui_settingsform.h"

settingsform::settingsform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingsform)
{
    ui->setupUi(this);
}

settingsform::~settingsform()
{
    delete ui;
}
