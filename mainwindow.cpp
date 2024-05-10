#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QSettings"
#include "QVariant"
#include "QFile"
#include "QSysInfo"

#include "QUrl"
#include "QDesktopServices"

#include "settingsdialog.h"
#include "infodialog.h"

#include "QStringEncryptionXOR.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings("GidraProject", "GidraPK");
    settings.beginGroup("Settings");
        QVariant sizeX = settings.value("sizeX", 800);
        QVariant sizeY = settings.value("sizeY", 500);
        QVariant color = settings.value("color");
        QVariant lang = settings.value("lang");
        this->customDatabasePath = settings.value("dbpath", "./database.db");
        QVariant firstStart = settings.value("isFirstStart", true);
    settings.endGroup();

    this->setGeometry(0, 0, sizeX.toInt(), sizeY.toInt());

    settings.setValue("/Settings/sizeX", this->size().width());
    settings.setValue("/Settings/sizeY", this->size().height());

    // Ready message;
    if (firstStart.toBool() == true)
    {
        settings.setValue("Settings/isFirstStart", false);
        ui->statusbar->showMessage("Welcome to Gidra! Look at the Help >> Manual.");
    }
    else ui->statusbar->showMessage("Gidra is ready!");

    // Working with styles
    if (settings.value("/Settings/color").toInt() == 1)
    {
        QFile styleFile( ":/style_dark.qss" );
        styleFile.open( QFile::ReadOnly );

        QString app_style( styleFile.readAll() );
        qApp->setStyleSheet(app_style);
    }
    else if (settings.value("/Settings/color").toInt() == 0)
    {
        QFile styleFile( ":/style_deafult.qss" );
        styleFile.open( QFile::ReadOnly );

        QString app_style( styleFile.readAll() );
        qApp->setStyleSheet(app_style);
    }

    //Hot keys
    CtrlQ = new QShortcut(this);
    CtrlQ->setKey(Qt::CTRL + Qt::Key_Q);
    connect(CtrlQ, SIGNAL(activated()), this, SLOT(close()));

    CtrlS = new QShortcut(this);
    CtrlQ->setKey(Qt::CTRL + Qt::Key_0);
    connect(CtrlS, SIGNAL(activated()), this, SLOT(openSettings()));

    CtrlE = new QShortcut(this);
    CtrlE->setKey(Qt::CTRL + Qt::Key_E);
    connect(CtrlE, SIGNAL(activated()), this, SLOT(/*export action*/));

    CtrlM = new QShortcut(this);
    CtrlM->setKey(Qt::CTRL + Qt::Key_M);
    connect(CtrlM, SIGNAL(activated()), this, SLOT(/*manual open action*/));

    Enter = new QShortcut(this);
    Enter->setKey(Qt::Key_Enter);
    connect(Enter, SIGNAL(activated()), this, SLOT(on_searchButton_clicked()));


    //System data
    QSysInfo sysinfo;

    QString systemInformation = "Gidra";
    systemInformation.append(sysinfo.currentCpuArchitecture());
    systemInformation.append(sysinfo.productVersion());
    systemInformation.append(sysinfo.machineUniqueId());
    systemInformation.append("Project");

    //Database
    setPasswordsModel(systemInformation);

    qDebug("Gidra is Ready!");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionettings_triggered()
{
    settingsdialog settingsdialog;

    settingsdialog.setModal(true);
    settingsdialog.exec();
}


void MainWindow::on_addButton_clicked()
{
    model->insertRow(model->rowCount());
}




void MainWindow::on_delButton_clicked()
{
    model->removeRow(row);
}




void MainWindow::on_mainPasswordsTable_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_searchButton_clicked()
{
    if (!ui->searchLineEdit->displayText().isEmpty())
        model->setFilter(QString("passname LIKE \"\%%1\%\"").arg(ui->searchLineEdit->text()));
    else
    {
        model->setTable("passwords");
        model->select();

        ui->mainPasswordsTable->setModel(model);
    }
}

void MainWindow::on_settingButton_clicked()
{
    openSettings();
}

void MainWindow::openSettings()
{
    settingsdialog settingsdialog;

    settingsdialog.setModal(false);
    settingsdialog.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    infodialog id;

    id.setModal(true);
    id.exec();
}


void MainWindow::on_actionManual_triggered()
{
    QDesktopServices::openUrl(QUrl("https://y-a-r-i-k.github.io/Gidra/manual.html"));
}

void MainWindow::on_LogutButton_clicked()
{
    close();
}

void MainWindow::saveAsCSV(QString filename)
{
  QFile f(filename);

  if( f.open( QIODevice::WriteOnly ) )
  {
    QTextStream ts( &f );
    QStringList strList;

    strList << "\" \"";
    for( int c = 0; c < ui->mainPasswordsTable->horizontalHeader()->count(); ++c )
      strList << "\""+ui->mainPasswordsTable->model()->headerData(c, Qt::Horizontal).toString()+"\"";
    ts << strList.join( ";" )+"\n";

    for( int r = 0; r < ui->mainPasswordsTable->verticalHeader()->count(); ++r )
    {
      strList.clear();
      strList << "\""+ui->mainPasswordsTable->model()->headerData(r, Qt::Vertical).toString()+"\"";
      for( int c = 0; c < ui->mainPasswordsTable->horizontalHeader()->count(); ++c )
      {
        strList << "\""+ui->mainPasswordsTable->model()->data(ui->mainPasswordsTable->model()->index(r, c), Qt::DisplayRole).toString()+"\"";
      }
      ts << strList.join( ";" )+"\n";
    }
    f.close();
  }
}


void MainWindow::on_actionLogout_triggered()
{
    close();
}

void MainWindow::setPasswordsModel(QString systemInformation)
{
    db = QSqlDatabase::addDatabase("SQLITECIPHER");
    db.setDatabaseName(this->customDatabasePath.toString());
    db.setPassword(QStringEncryptionXOR::cryptString(systemInformation));

    db.setConnectOptions("QSQLITE_USE_CIPHER=aes256cbc;");

    if (!db.open()) {qWarning("ERROR: Database;");}

    ui->mainPasswordsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE passwords (passname TEXT, password TEXT)");

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("passwords");
    model->select();

    ui->mainPasswordsTable->setModel(model);}



