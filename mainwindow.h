#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QString>
#include <QSettings>
#include <QTranslator>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void saveAsCSV(QString);
    void setPasswordsModel(QString);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionettings_triggered();

    void on_addButton_clicked();

    void on_delButton_clicked();

    void on_mainPasswordsTable_clicked(const QModelIndex &index);

    void on_searchButton_clicked();


    void on_LogutButton_clicked();

    void on_settingButton_clicked();

    void on_actionAbout_triggered();

    void on_actionManual_triggered();

    void on_actionLogout_triggered();

    void openSettings();

private:

    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    int row;

    QVariant customDatabasePath;

    QShortcut *CtrlM; //Open manual
    QShortcut *CtrlE; //Export
    QShortcut *CtrlQ; //Exit the app
    QShortcut *CtrlS; //Settings
    QShortcut *Enter; //Search


};
#endif // MAINWINDOW_H
