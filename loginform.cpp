#include "loginform.h"
#include "ui_loginform.h"
#include "mainwindow.h"

#include <QFile>
#include <QTranslator>
#include <QDebug>



loginform::loginform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginform)
{
    ui->setupUi(this);

    QSettings Psettings("GidraProject", "GidraPK");
    Psettings.beginGroup("SetPassword");
        this->pass = Psettings.value("Password", "password");
        this->databasepassword = Psettings.value("DatabasePassword", "password");
    Psettings.endGroup();

    QFile styleFile( ":/login.qss" );
    styleFile.open( QFile::ReadOnly );

    QString app_style( styleFile.readAll() );
    qApp->setStyleSheet(app_style);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->passwordLineEdit->setAlignment(Qt::AlignCenter);

    loginByEnter = new QShortcut(this);
    loginByEnter->setKey(Qt::Key_Return);

    connect(loginByEnter, SIGNAL(activated()), this, SLOT(login()));


}

loginform::~loginform()
{
    delete ui;
}

void loginform::on_loginButton_clicked()
{

    this->login();
}


void loginform::login()
{
    if (ui->passwordLineEdit->text() == this->pass.toString())
    {
        MainWindow *w = new MainWindow;
        w->show();
        close();
    }

    else
    {
        ui->labelError->setText(tr("Wrong password, try again."));
        ui->passwordLineEdit->clear();
    }
}


void loginform::on_showCheckBox_stateChanged(int arg1)
{
    if (ui->showCheckBox->checkState() == Qt::Unchecked)
    {
        qDebug("!!!");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    }

    else if (ui->showCheckBox->checkState() == Qt::Checked)
    {
        qDebug("###");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    }

}

